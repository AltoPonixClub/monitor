package io.github.altoponix.plantsegmentation;

import javafx.fxml.FXML;
import javafx.scene.control.CheckBox;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.FileChooser;
import org.opencv.core.*;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class SegmentationController {
    @FXML
    private ImageView imageView;
    @FXML
    private ImageView maskView;
    @FXML
    private TextField hmin;
    @FXML
    private TextField smin;
    @FXML
    private TextField vmin;
    @FXML
    private TextField hmax;
    @FXML
    private TextField smax;
    @FXML
    private TextField vmax;
    @FXML
    private CheckBox eyedropper;
    @FXML
    private TextField eyedropperBounds;
    @FXML
    private TextField brushSize;

    private String filePath;
    private Mat image = new Mat();
    private Mat oldImage = new Mat();
    private Mat mask = new Mat();
    private Mat oldMask = new Mat();
    private Mat maskOut = new Mat();
    private Mat oldMaskOut = new Mat();
    private List<MatOfPoint> contours = new ArrayList<>();
    private Mat hierarchy = new Mat();
    private double fitScale;
    private boolean fitSide;

    //imports a photo using JavaFX FileChooser
    @FXML
    public void importPhoto() {
        FileChooser fileChooser = new FileChooser();
        File file = fileChooser.showOpenDialog(Main.getStageAccess());
        if(file != null) {
            filePath = file.toURI().toString().substring(6);
            image = Imgcodecs.imread(filePath);
            mask = new Mat(image.rows(), image.cols(), CvType.CV_8U, Scalar.all(0));
            maskOut = new Mat(image.rows(), image.cols(), CvType.CV_8U, Scalar.all(0));
            fitSide = image.cols() >= image.rows();
            if (fitSide) {
                fitScale = image.cols() / 600.0;
            } else {
                fitScale = image.rows() / 600.0;
            }
            update();
        }
    }

    //updates the image with filters
    public void updateStage() {
        updateImage(imageView, image);
        updateImage(maskView, mask);
    }

    private void updateImage(ImageView imageView, Mat mat) {
        imageView.setImage(matToImage(mat));
        imageView.setPreserveRatio(true);
        if (fitSide) {
            imageView.setFitWidth(600);
        } else {
            imageView.setFitHeight(600);
        }
        imageView.setPickOnBounds(true);
        imageView.setOnMouseClicked(e -> {
            mouseEvent(e.getX()*fitScale, e.getY()*fitScale);
        });
        imageView.setOnMouseDragged(e -> {
            mouseEvent(e.getX()*fitScale, e.getY()*fitScale);
        });
    }

    @FXML
    public void save() {
        String filename = filePath.substring(0, filePath.indexOf("."));
        Imgcodecs.imwrite(filename + "_mask.png", maskOut);
        System.out.println("Image saved");
    }

    @FXML
    public void undo() {
        System.out.println("Undo");
        image = oldImage.clone();
        mask = oldMask.clone();
        maskOut = oldMaskOut.clone();
        updateStage();
    }

    //eyedropper and drawing
    public void mouseEvent(double x, double y) {
        if (eyedropper.isSelected()) {
            double[] hsv = image.get((int)x, (int)y);
            double bounds = Double.parseDouble(eyedropperBounds.getText());
            hmin.setText(String.valueOf(hsv[0] - bounds));
            smin.setText(String.valueOf(hsv[1] - bounds));
            vmin.setText(String.valueOf(hsv[2] - bounds));
            hmax.setText(String.valueOf(hsv[0] + bounds));
            smax.setText(String.valueOf(hsv[1] + bounds));
            vmax.setText(String.valueOf(hsv[2] + bounds));
        } else {
            oldImage = image.clone();
            oldMask = mask.clone();
            oldMaskOut = maskOut.clone();
            int size = Integer.parseInt(brushSize.getText());
            int v = 0;

            Imgproc.circle(image, new Point(x, y), size, new Scalar(0, 255, 0), Imgproc.FILLED);
            Imgproc.circle(mask, new Point(x, y), size, Scalar.all(255), Imgproc.FILLED);
            Imgproc.circle(maskOut, new Point(x, y), size, Scalar.all(255), Imgproc.FILLED);

            for (MatOfPoint contour:contours) {
                v++;
                for (int i = 0; i < v; i++) {
                    MatOfPoint2f convertedContour = new MatOfPoint2f(contours.get(i).toArray());
                    double r = Imgproc.pointPolygonTest(convertedContour, new Point(x, y), false);
                    if (r == 1) {
                        List<MatOfPoint> contourArray = new ArrayList<MatOfPoint>();
                        contourArray.add( new MatOfPoint(contours.get(i).toArray()));
                        Imgproc.fillPoly(image, contourArray, new Scalar(0, 255, 0));
                        Imgproc.fillPoly(mask, contourArray, Scalar.all(255));
                        Imgproc.fillPoly(maskOut, contourArray, Scalar.all(255));
                        Imgproc.polylines(mask, contourArray, true, Scalar.all(255), 2);
                        Imgproc.polylines(maskOut, contourArray, true, Scalar.all(255), 2);
                    }
                }
            }
            updateStage();
        }
    }

    //applies filters and draws contours
    @FXML
    private void update() {
        oldImage = image.clone();
        oldMask = mask.clone();
        oldMaskOut = maskOut.clone();
        contours = new ArrayList<>();
        Mat color = doColorFilter(Imgcodecs.imread(filePath));
        getContours(color);
        updateStage();
    }

    //convert mat to png image that can be displayed in JavaFX
    private Image matToImage(Mat mat) {
        MatOfByte buffer = new MatOfByte();
        Imgcodecs.imencode(".png", mat, buffer);
        return new Image(new ByteArrayInputStream(buffer.toArray()));
    }

    //filter colors using HSV and returns mat
    private Mat doColorFilter(Mat mat){
        Mat hsvImage = new Mat();
        Mat mask = new Mat();
        Mat result = new Mat();
        //convert mat from BGR to HSV
        Imgproc.cvtColor(mat, hsvImage, Imgproc.COLOR_BGR2HSV);
        //create a mask within a range of HSV values
        Core.inRange(hsvImage,
                new Scalar(Double.parseDouble(hmin.getText()), Double.parseDouble(smin.getText()),Double.parseDouble(vmin.getText())),
                new Scalar(Double.parseDouble(hmax.getText()), Double.parseDouble(smax.getText()),Double.parseDouble(vmax.getText())),
                mask);
        Core.bitwise_and(mat, mat, result, mask);
        return result;
    }

    //draws and returns list of contours
    private void getContours(Mat mat) {
        Mat gray = new Mat();
        Imgproc.cvtColor(mat, gray, Imgproc.COLOR_HSV2RGB);
        Imgproc.cvtColor(mat, gray, Imgproc.COLOR_RGB2GRAY);
        Imgproc.findContours(gray, this.contours, this.hierarchy, Imgproc.RETR_LIST, Imgproc.CHAIN_APPROX_SIMPLE);
        Imgproc.drawContours(image, contours, -1, new Scalar(0, 255, 0), 5);
        Imgproc.drawContours(mask, contours, -1, Scalar.all(255), 5);
    }
}