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
    TextField eyedropperBounds;

    private String filePath;
    private Mat image = new Mat();
    private Mat mask = new Mat();
    private Mat maskOut = new Mat();
    private List<MatOfPoint> contours = new ArrayList<>();
    private Mat hierarchy = new Mat();

    //imports a photo using JavaFX FileChooser
    @FXML
    public void importPhoto() {
        FileChooser fileChooser = new FileChooser();
        File file = fileChooser.showOpenDialog(Main.getStageAccess());
        if(file != null) {
            filePath = file.toURI().toString().substring(5);
            image = Imgcodecs.imread(filePath);
            mask = new Mat(image.rows(), image.cols(), CvType.CV_8U, Scalar.all(0));
            maskOut = new Mat(image.rows(), image.cols(), CvType.CV_8U, Scalar.all(0));
            update();
        }
    }

    //updates the image with filters
    public void updateStage() {
        imageView.setImage(matToImage(image));
        imageView.setPreserveRatio(true);
        imageView.setFitWidth(400);

        imageView.setPickOnBounds(true);
        imageView.setOnMousePressed(e -> {
            mouseEvent(e.getX(), e.getY());
        });

        maskView.setImage(matToImage(mask));
        maskView.setPreserveRatio(true);
        maskView.setFitWidth(400);

        maskView.setPickOnBounds(true);
        maskView.setOnMousePressed(e -> {
            mouseEvent(e.getX(), e.getY());
        });
    }

    @FXML
    public void save() {
        String filename = filePath.substring(0, filePath.length()-4);
        Imgcodecs.imwrite(filename + "_mask.png", maskOut);
    }

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
            int v = 0;

            Imgproc.circle(image, new Point(x, y), 3, new Scalar(0, 255, 0), Imgproc.FILLED);
            Imgproc.circle(mask, new Point(x, y), 3, Scalar.all(255), Imgproc.FILLED);
            Imgproc.circle(maskOut, new Point(x, y), 3, Scalar.all(255), Imgproc.FILLED);

            for (MatOfPoint contour:contours) {
                v++;
                for (int i = 0; i < v; i++) {
                    MatOfPoint2f convertedContour = new MatOfPoint2f(contour.toArray());
                    double r = Imgproc.pointPolygonTest(convertedContour, new Point(x, y), false);
                    if (r == 1) {
                        Imgproc.fillPoly(image, contours, new Scalar(0, 255, 0));
                        Imgproc.fillPoly(mask, contours, Scalar.all(255));
                        Imgproc.fillPoly(maskOut, contours, Scalar.all(255));
                        Imgproc.polylines(mask, contours, true, Scalar.all(255), 2);
                        Imgproc.polylines(maskOut, contours, true, Scalar.all(255), 2);
                    }
                }
            }

            updateStage();
        }
    }

    @FXML
    private void update() {
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
        Core.add(hsvImage, Scalar.all(0), result);
        mat.copyTo(result, mask);
        return result;
    }

    //draws and returns list of contours
    private void getContours(Mat mat) {
        Mat gray = new Mat();
        Imgproc.cvtColor(mat, gray, Imgproc.COLOR_HSV2RGB);
        Imgproc.cvtColor(mat, gray, Imgproc.COLOR_RGB2GRAY);
        Imgproc.findContours(gray, this.contours, this.hierarchy, Imgproc.RETR_EXTERNAL, Imgproc.CHAIN_APPROX_SIMPLE);
        Imgproc.drawContours(image, contours, -1, new Scalar(0, 255, 0), 2);
        Imgproc.drawContours(mask, contours, -1, Scalar.all(255), 2);
    }
}