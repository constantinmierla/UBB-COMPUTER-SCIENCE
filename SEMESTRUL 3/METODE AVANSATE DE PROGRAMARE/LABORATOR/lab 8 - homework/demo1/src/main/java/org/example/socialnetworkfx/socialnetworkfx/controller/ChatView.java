package org.example.socialnetworkfx.socialnetworkfx.controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import org.example.socialnetworkfx.socialnetworkfx.domain.Message;
import org.example.socialnetworkfx.socialnetworkfx.domain.event.MessageEntityChange;
import org.example.socialnetworkfx.socialnetworkfx.service.MessageService;
import org.example.socialnetworkfx.socialnetworkfx.service.UserService;
import org.example.socialnetworkfx.socialnetworkfx.utils.observer.Observer;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class ChatView implements Observer<MessageEntityChange> {
    @FXML
    public ListView<String> listView;
    @FXML
    public TextField messageText;
    @FXML
    public Button sendButton;
    @FXML
    public Label nameLabelChat;
    @FXML
    public Button replyButton;

    private MessageService messageService;
    private UserService userService;
    private Long IdTo;
    private Long IdFrom;
    String receiver;
    ObservableList<String> model = FXCollections.observableArrayList();

    public void setService(MessageService messageService,UserService userService,Long IdTo,Long IdFrom,String name) {
        this.messageService = messageService;
        this.userService = userService;
        this.IdTo = IdTo;
        this.IdFrom = IdFrom;
        this.receiver = name;
        messageService.addObserver(this);
        initModel();
    }

    public void handleSend(ActionEvent actionEvent) {
        String message = messageText.getText();
        messageService.save(IdTo,IdFrom,message);
        messageText.clear();
    }
    public void initialize() {

        listView.setItems(model);
    }

    private void initModel() {
        Iterable<Message> messages = messageService.getConversation(IdTo,IdFrom);
        ArrayList<String> all=new ArrayList<>();
        for(Message m : messages) {
            String name = userService.findOne(m.getFrom()).getFirstName() + " " + userService.findOne(m.getFrom()).getLastName();
            if(m.getFrom().equals(IdFrom)) {
                name="You";
            }
            if (messageService.findRepliedText(m.getID())!=null) {
                Message replyText=messageService.findRepliedText(m.getID());
                String line = name + " replied to " + replyText.getMessage() + ": " + m.getMessage();
                all.add(line);
            } else {

                String line = name + ": " + m.getMessage();
                all.add(line);
            }
        }

        model.setAll(all);
        nameLabelChat.setText(receiver);
    }

    @Override
    public void update(MessageEntityChange messageEntityChange) {
        initModel();
    }

    public void handleReply(ActionEvent actionEvent) {
        String row=listView.getSelectionModel().getSelectedItem();
        LinkedList<String> list = new LinkedList<>(Arrays.stream(row.split(": ")).toList());
        String rawMessage = list.getLast();

        Message initialMessage=messageService.findByMessage(rawMessage);

        String text = messageText.getText();
        messageService.save(IdTo,IdFrom,text);

        Message replyMessage=messageService.findByMessage(text);




        initialMessage.setReply(replyMessage.getID());


        messageService.update(initialMessage.getID(), initialMessage.getTo(), initialMessage.getFrom(),initialMessage.getMessage(),initialMessage.getTime(), initialMessage.getReply());

        messageText.clear();

    }
}
