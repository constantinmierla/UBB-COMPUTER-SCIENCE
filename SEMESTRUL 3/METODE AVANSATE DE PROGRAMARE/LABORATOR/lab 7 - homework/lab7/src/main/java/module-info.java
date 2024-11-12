module org.example.lab7 {
    requires javafx.controls;
    requires javafx.fxml;


    opens org.example.lab7 to javafx.fxml;
    exports org.example.lab7;
}