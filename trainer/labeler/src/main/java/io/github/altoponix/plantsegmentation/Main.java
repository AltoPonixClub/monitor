package io.github.altoponix.plantsegmentation;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

import org.opencv.core.Core;

import java.io.IOException;
import java.util.Objects;

public class Main extends Application {

    private static Stage stageAccess;

    @Override
    public void start(Stage stage) throws IOException {
        stageAccess = stage;
        BorderPane root = (BorderPane) FXMLLoader.load(Objects.requireNonNull(Main.class.getResource("segmentation-view.fxml")));
        root.setStyle("-fx-background-color: whitesmoke;");
        Scene scene = new Scene(root, 1920, 1080);
        stage.setTitle("Image Segmentation");
        stage.setScene(scene);
        stage.show();
    }

    public static javafx.stage.Stage getStageAccess() {
        return stageAccess;
    }

    public static void main(String[] args) {
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
        launch();
    }
}