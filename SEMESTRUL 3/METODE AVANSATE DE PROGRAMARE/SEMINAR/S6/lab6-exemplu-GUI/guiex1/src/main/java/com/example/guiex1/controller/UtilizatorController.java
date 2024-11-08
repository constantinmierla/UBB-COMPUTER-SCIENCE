package com.example.guiex1.controller;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.ValidationException;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;




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
    @FXML
    TextField firstNameField;
    @FXML
    TextField lastNameField;
    public void setUtilizatorService(UtilizatorService service) {
        this.service = service;
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
//        Iterable<Utilizator> messages = service.getAll();
//        List<Utilizator> users = StreamSupport.stream(messages.spliterator(), false)
//                .collect(Collectors.toList());
//        model.setAll(users);
    }
    public void handleUpdateUtilizator(ActionEvent actionEvent){
        Utilizator user = (Utilizator) tableView.getSelectionModel().getSelectedItem();
        if(user != null){
            Utilizator newUser = new Utilizator(firstNameField.getText(), lastNameField.getText());
            newUser.setId(user.getId());
            Utilizator updated = service.updateUtilizator(user);
        }
    }
    public void handleAddUtilizator(ActionEvent actionEvent){
        ///TODO
    }
    public void handleDeleteUtilizator(ActionEvent actionEvent) {
        Utilizator user=(Utilizator) tableView.getSelectionModel().getSelectedItem();
        if (user!=null) {
            Utilizator deleted= service.deleteUtilizator(user.getId());
        }
    }
}
