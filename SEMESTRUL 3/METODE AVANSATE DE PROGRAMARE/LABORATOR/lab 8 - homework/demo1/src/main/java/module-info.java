module org.example.socialnetworkfx {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.web;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires net.synedra.validatorfx;
    requires org.kordamp.ikonli.javafx;
    requires org.kordamp.bootstrapfx.core;
    requires eu.hansolo.tilesfx;
    requires com.almasb.fxgl.all;
    requires java.sql;
    requires org.jgrapht.core;
    requires jdk.jfr;
    requires java.desktop;

    opens org.example.socialnetworkfx.socialnetworkfx to javafx.fxml;
    exports org.example.socialnetworkfx.socialnetworkfx;
    exports org.example.socialnetworkfx.socialnetworkfx.controller;
    opens org.example.socialnetworkfx.socialnetworkfx.controller to javafx.fxml;
    opens org.example.socialnetworkfx.socialnetworkfx.domain to javafx.base;

}