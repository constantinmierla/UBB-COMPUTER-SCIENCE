package org.example.s8bun;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
public class HelloController {
    @FXML
    private Label welcomeText;
    @FXML
    public TextField NumeStudent;

    @FXML
    public TextField NotaMare;
    @FXML
    public TextField TemaText;
    @FXML
    protected void onHelloButtonClick() {
        welcomeText.setText("Welcome to JavaFX Application!");
    }
}