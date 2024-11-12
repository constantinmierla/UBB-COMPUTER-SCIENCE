package com.example.guiex1.controller;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;


import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UtilizatorController implements Observer<UtilizatorEntityChangeEvent> {
    UtilizatorService service;
    ObservableList<Utilizator> model = FXCollections.observableArrayList();


    @FXML
    TableView<Utilizator> tableView;
    @FXML
    TableColumn<Utilizator,String> tableColumnFirstName;
    @FXML
    TableColumn<Utilizator,String> tableColumnLastName;


    public void setUtilizatorService(UtilizatorService service) {
        this.service = service;
        service.addObserver(this);
        initModel();
    }

    @FXML
    public void initialize() {
        tableColumnFirstName.setCellValueFactory(new PropertyValueFactory<Utilizator, String>("firstName"));
        tableColumnLastName.setCellValueFactory(new PropertyValueFactory<Utilizator, String>("lastName"));
        tableView.setItems(model);
    }

    private void initModel() {
        Iterable<Utilizator> messages = service.getAll();
        List<Utilizator> users = StreamSupport.stream(messages.spliterator(), false)
                .collect(Collectors.toList());
        model.setAll(users);
    }

    @Override
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        initModel();
    }

    public void handleAddUtilizator(ActionEvent actionEvent) {

    }

    public void handleDeleteUtilizator(ActionEvent actionEvent) {
        Utilizator user=(Utilizator) tableView.getSelectionModel().getSelectedItem();
        if (user!=null) {
            Utilizator deleted= service.deleteUtilizator(user.getId());
            MessageAlert.showMessage(null, Alert.AlertType.CONFIRMATION,"Delete user","Userul a fost sters");
        }
        else MessageAlert.showErrorMessage(null, "NU ati selectat nici un utilizator");
    }

    public void handleUpdateUtilizator(ActionEvent actionEvent) {
        // TODO
        Utilizator selected = tableView.getSelectionModel().getSelectedItem();
        if (selected != null) {
            showMessageTaskEditDialog(selected);
        } else
            MessageAlert.showErrorMessage(null, "NU ati selectat nici un student");

    }

    public void showMessageTaskEditDialog(Utilizator user) {
        try {
            // create a new stage for the popup dialog.
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("../views/edit-user-view.fxml"));

            AnchorPane root = (AnchorPane) loader.load();

            // Create the dialog Stage.
            Stage dialogStage = new Stage();
            dialogStage.setTitle("Edit Message");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            //dialogStage.initOwner(primaryStage);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            EditUserController editUserController = loader.getController();
            editUserController.setService(service, dialogStage, user);

            dialogStage.show();

        } catch ( IOException e) {
            e.printStackTrace();
        }
    }
}
