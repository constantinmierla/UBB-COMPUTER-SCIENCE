module org.example.s8bun {
    requires javafx.controls;
    requires javafx.fxml;


    opens org.example.s8bun to javafx.fxml;
    exports org.example.s8bun;
}