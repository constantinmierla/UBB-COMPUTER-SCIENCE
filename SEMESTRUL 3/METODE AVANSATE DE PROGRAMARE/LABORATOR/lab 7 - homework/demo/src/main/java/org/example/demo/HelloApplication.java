package org.example.demo;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage primaryStage) throws IOException {
        System.out.println("COCO");
        initView(primaryStage);
        primaryStage.setWidth(800);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

    private void initView(Stage primaryStage) {
        try {
            // Loading FXML with relative path
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/guiex1/views/hello-view.fxml"));
            AnchorPane userLayout = fxmlLoader.load();
            primaryStage.setScene(new Scene(userLayout));

            // Optional: Get the controller if needed and set services
            // YourController controller = fxmlLoader.getController();
            // controller.setSomeService(someService);

        } catch (IOException e) {
            e.printStackTrace();
            throw new RuntimeException("Error loading FXML", e);
        }
    }
}
