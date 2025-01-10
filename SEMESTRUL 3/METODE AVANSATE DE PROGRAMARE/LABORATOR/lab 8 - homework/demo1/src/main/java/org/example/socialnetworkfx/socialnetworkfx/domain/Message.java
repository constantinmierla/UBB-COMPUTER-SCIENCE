package org.example.socialnetworkfx.socialnetworkfx.domain;

import java.time.LocalDateTime;

public class Message extends Entity<Long>{
    private Long to;
    private Long from;
    private String message;
    private LocalDateTime time;
    private Long reply;

    public Message(Long to, Long from, String message) {
        this.to = to;
        this.from = from;
        this.message = message;
        this.time = LocalDateTime.now();
        this.reply=null;
    }
    public Long getTo() {
        return to;
    }

    public void setTo(Long to) {
        this.to = to;
    }

    public Long getFrom() {
        return from;
    }

    public void setFrom(Long from) {
        this.from = from;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public LocalDateTime getTime() {
        return time;
    }

    public void setTime(LocalDateTime time) {
        this.time = time;
    }
    @Override
    public String toString() {
        return from+": "+message;
    }

    public Long getReply() {
        return reply;
    }

    public void setReply(Long reply) {
        this.reply = reply;
    }
}
