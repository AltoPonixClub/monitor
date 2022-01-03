package io.github.altoponix.plantsegmentation;

import javafx.fxml.FXML;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
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
    private CheckBox eraser;
    @FXML
    private CheckBox eyedropper;
    @FXML
    private TextField eyedropperBounds;
    @FXML
    private TextField brushSize;
    @FXML
    private TextField folderPath;
    @FXML
    private TextField outputPath;
    @FXML
    private TextField photoIndex;
    @FXML
    private Label totalPhotos;
    @FXML
    private TextField blur;
    @FXML
    private TextField ffBounds;
    @FXML
    private TextField opacity;

    private String filePath;
    private Mat original = new Mat();
    private Mat image = new Mat();
    private ArrayList<Mat> oldImage = new ArrayList<>();
    private Mat mask = new Mat();
    private ArrayList<Mat> oldMask = new ArrayList<>();
    private Mat maskOut = new Mat();
    private ArrayList<Mat> oldMaskOut = new ArrayList<>();
    private List<MatOfPoint> contours = new ArrayList<>();
    private Mat hierarchy = new Mat();
    private double fitScale;
    private boolean fitSide;
    private File[] files;
    private int filesIndex = 1;
    private Mat floodfillMask = new Mat();

    @FXML
    public void updatePath() {
        File dir = new File(folderPath.getText());
        files = dir.listFiles();
        if (files != null) {
            photoIndex.setText("1");
            totalPhotos.setText(String.valueOf(files.length));
            photoIndex.setText(String.valueOf(filesIndex));
            loadPhoto(files[filesIndex-1]);
        } else {
            System.out.println("Invalid Directory");
        }
    }

    @FXML
    public void nextPhoto() {
        filesIndex++;
        photoIndex.setText(String.valueOf(filesIndex));
        loadPhoto(files[filesIndex-1]);
    }

    @FXML
    public void updateIndex() {
        filesIndex = Integer.parseInt(photoIndex.getText());
        loadPhoto(files[filesIndex-1]);
    }

    private void loadPhoto(File file) {
        if(file != null) {
            //set this 6 to a 5 on mac
            filePath = file.toURI().toString().substring(6);
            image = Imgcodecs.imread(filePath);
            original = Imgcodecs.imread(filePath);
            mask = new Mat(image.rows(), image.cols(), CvType.CV_8U, Scalar.all(0));
            maskOut = new Mat(image.rows(), image.cols(), CvType.CV_8U, Scalar.all(0));
            floodfillMask = new Mat(image.rows()+2, image.cols()+2, CvType.CV_8U, Scalar.all(0));
            oldImage.removeAll(oldImage);
            oldImage.add(image);
            oldMask.removeAll(oldMask);
            oldMask.add(mask);
            oldMaskOut.removeAll(oldMaskOut);
            oldMaskOut.add(maskOut);
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
        Mat weightedImage = new Mat();
        double opacity = Double.parseDouble(this.opacity.getText())/100;
        Core.addWeighted(image, opacity, original, 1-opacity, 0, weightedImage);
        updateImage(imageView, weightedImage);
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
        String filename = outputPath.getText() + filePath.substring(folderPath.getText().length(), filePath.indexOf(".")) + "_mask.png";
        Imgcodecs.imwrite(filename, maskOut);
        System.out.println("Image saved at " + filename);
    }

    @FXML
    public void undo() {
        System.out.println("Undo");
        if (oldImage.size() > 0) {
            image = oldImage.get(oldImage.size()-1).clone();
            mask = oldMask.get(oldMask.size()-1).clone();
            maskOut = oldMaskOut.get(oldMaskOut.size()-1).clone();
            oldImage.remove(oldImage.size()-1);
            oldMask.remove(oldMask.size()-1);
            oldMaskOut.remove(oldMaskOut.size()-1);
        }
        updateStage();
    }

    //eyedropper and drawing
    public void mouseEvent(double x, double y) {
        if (eyedropper.isSelected()) {
            Mat hsvMat = new Mat();
            Imgproc.cvtColor(image, hsvMat, Imgproc.COLOR_BGR2HSV);
            double[] hsv = image.get((int)y, (int)x);
            double bounds = Double.parseDouble(eyedropperBounds.getText());
            hmin.setText(String.valueOf(hsv[0] - bounds));
            smin.setText(String.valueOf(hsv[1] - bounds));
            vmin.setText(String.valueOf(hsv[2] - bounds));
            hmax.setText(String.valueOf(hsv[0] + bounds));
            smax.setText(String.valueOf(hsv[1] + bounds));
            vmax.setText(String.valueOf(hsv[2] + bounds));
        } else {
            if (oldImage.size() > 100) {
                oldImage.remove(0);
                oldMask.remove(0);
                oldMaskOut.remove(0);
            }
            oldImage.add(image.clone());
            oldMask.add(mask.clone());
            oldMaskOut.add(maskOut.clone());

            int size = Integer.parseInt(brushSize.getText());
            int floodFill = Integer.parseInt(ffBounds.getText());
            Scalar floodFillBounds = new Scalar(floodFill, floodFill, floodFill);

            if (eraser.isSelected()) {
                Imgproc.circle(image, new Point(x, y), size, new Scalar(0, 0, 0), Imgproc.FILLED);
                Imgproc.circle(mask, new Point(x, y), size, Scalar.all(0), Imgproc.FILLED);
                Imgproc.circle(maskOut, new Point(x, y), size, Scalar.all(0), Imgproc.FILLED);
            } else {
                int v = 0;

                Mat imageFFMask = floodfillMask.clone();
                Mat maskFFMask = floodfillMask.clone();
                Mat maskOutFFMask = floodfillMask.clone();

                for (MatOfPoint contour : contours) {
                    v++;
                    for (int i = 0; i < v; i++) {
                        MatOfPoint2f convertedContour = new MatOfPoint2f(contours.get(i).toArray());
                        double r = Imgproc.pointPolygonTest(convertedContour, new Point(x, y), false);
                        if (r == 1) {
                            Imgproc.floodFill(image, imageFFMask, new Point(x, y), new Scalar(0, 255, 0), new Rect(), floodFillBounds, floodFillBounds, 8 | (255 << 8));
                            Imgproc.floodFill(mask, maskFFMask, new Point(x, y), Scalar.all(255), new Rect(), floodFillBounds, floodFillBounds, 8 | (255 << 8));
                            Imgproc.floodFill(maskOut, maskOutFFMask, new Point(x, y), Scalar.all(255), new Rect(), floodFillBounds, floodFillBounds, 8 | (255 << 8));
                        }
                    }
                }

                Imgproc.circle(image, new Point(x, y), size, new Scalar(0, 255, 0), Imgproc.FILLED);
                Imgproc.circle(mask, new Point(x, y), size, Scalar.all(255), Imgproc.FILLED);
                Imgproc.circle(maskOut, new Point(x, y), size, Scalar.all(255), Imgproc.FILLED);
            }

            Imgproc.drawContours(image, contours, -1, new Scalar(0, 0, 255), 2);
            Imgproc.drawContours(mask, contours, -1, Scalar.all(100), 2);
            updateStage();
        }
    }

    //applies filters and draws contours
    @FXML
    private void update() {
        if (oldImage.size() > 100) {
            oldImage.remove(0);
            oldMask.remove(0);
            oldMaskOut.remove(0);
        }
        oldImage.add(image.clone());
        oldMask.add(mask.clone());
        oldMaskOut.add(maskOut.clone());
        contours = new ArrayList<>();
        Mat color = doColorFilter(Imgcodecs.imread(filePath));
        Mat blur = blur(color);
        getContours(blur);
        updateStage();
    }

    //convert mat to png image that can be displayed in JavaFX
    private Image matToImage(Mat mat) {
        MatOfByte buffer = new MatOfByte();
        Imgcodecs.imencode(".png", mat, buffer);
        return new Image(new ByteArrayInputStream(buffer.toArray()));
    }

    //filter colors using HSV and returns mat
    private Mat doColorFilter(Mat mat) {
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

    private Mat blur(Mat mat) {
        Mat result = new Mat();
        Mat kernel = Mat.ones(Integer.parseInt(blur.getText()),Integer.parseInt(blur.getText()), CvType.CV_32F);

        Imgproc.morphologyEx(mat, result, Imgproc.MORPH_OPEN, kernel);
        Imgproc.morphologyEx(result, result, Imgproc.MORPH_CLOSE, kernel);
        return result;
    }

    //draws and returns list of contours
    private void getContours(Mat mat) {
        Mat gray = new Mat();
        Imgproc.cvtColor(mat, gray, Imgproc.COLOR_HSV2RGB);
        Imgproc.cvtColor(mat, gray, Imgproc.COLOR_RGB2GRAY);
        Imgproc.findContours(gray, this.contours, this.hierarchy, Imgproc.RETR_LIST, Imgproc.CHAIN_APPROX_SIMPLE);
        Imgproc.drawContours(image, contours, -1, new Scalar(0, 0, 255), 2);
        Imgproc.drawContours(mask, contours, -1, Scalar.all(100), 2);
        Imgproc.drawContours(floodfillMask, contours, -1, Scalar.all(255), 2);
    }
}
