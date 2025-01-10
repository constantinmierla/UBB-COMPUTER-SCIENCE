package org.example.socialnetworkfx.socialnetworkfx.service;

import org.example.socialnetworkfx.socialnetworkfx.domain.Message;
import org.example.socialnetworkfx.socialnetworkfx.domain.event.ChangeEventType;
import org.example.socialnetworkfx.socialnetworkfx.domain.event.MessageEntityChange;
import org.example.socialnetworkfx.socialnetworkfx.repository.MessageDbRepository;
import org.example.socialnetworkfx.socialnetworkfx.utils.observer.Observable;
import org.example.socialnetworkfx.socialnetworkfx.utils.observer.Observer;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class MessageService implements Service<Message>, Observable<MessageEntityChange> {
    private MessageDbRepository repository;
    private List<Observer<MessageEntityChange>> observers = new ArrayList<>();

    public MessageService(MessageDbRepository repository) {
        this.repository = repository;
    }

    @Override
    public Message delete(Long ID) {
        Message m = repository.delete(ID).orElse(null);
        MessageEntityChange messageEntityChange = new MessageEntityChange(ChangeEventType.DELETE, m);
        notifyObservers(messageEntityChange);
        return m;
    }

    @Override
    public Iterable<Message> findAll() {
        return repository.findAll();
    }

    public Message save(Long to, Long from, String text) {
        Message m = new Message(to, from, text);
        Message a = repository.save(m).orElse(null);
        MessageEntityChange messageEntityChange = new MessageEntityChange(ChangeEventType.ADD, a);
        notifyObservers(messageEntityChange);
        return m;
    }

    public Message findOne(Long ID) {
        return repository.findOne(ID).orElse(null);
    }

    public Message update(Long id, Long to, Long from, String text, LocalDateTime time,Long reply) {
        Message m = new Message(to, from, text);
        m.setReply(reply);
        m.setID(id);
        m.setTime(time);

        Message a = repository.update(m).orElse(null);
        MessageEntityChange messageEntityChange = new MessageEntityChange(ChangeEventType.UPDATE, a);
        notifyObservers(messageEntityChange);
        return m;
    }

    public List<Message> getConversation(Long to, Long from) {
        ArrayList<Message> list = new ArrayList<>();
        for (Message message : repository.findAll()) {
            if (message.getTo().equals(to) && message.getFrom().equals(from)) {
                list.add(message);
            } else if (message.getTo().equals(from) && message.getFrom().equals(to)) {
                list.add(message);
            }
        }
        return list.stream().sorted(Comparator.comparing(Message::getTime))
                .collect(Collectors.toList());
    }

    public void removeByID(Long ID) {
        Iterable<Message> messages = repository.findAll();
        for (Message message : messages) {
            if (message.getFrom().equals(ID) || message.getTo().equals(ID)) {
                repository.delete(message.getID());
            }
        }
    }
    public Message findByMessage(String message){
        Iterable<Message> all=repository.findAll();
        for(Message m:all){
            if(m.getMessage().equals(message)){
                return m;
            }
        }
        return null;
    }
    public Message findRepliedText(Long id){
        Iterable<Message> all=repository.findAll();
        for(Message m:all) {
            if (m.getReply() != null) {
                if (m.getReply().equals(id)) {
                    return m;
                }
            }
        }
        return null;
    }

    @Override
    public void addObserver(Observer<MessageEntityChange> e) {
        observers.add(e);

    }

    @Override
    public void removeObserver(Observer<MessageEntityChange> e) {
        //observers.remove(e);
    }

    @Override
    public void notifyObservers(MessageEntityChange t) {

        observers.stream().forEach(x -> x.update(t));
    }

}
