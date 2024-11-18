package org.example.socialnetworkfx.socialnetworkfx.domain.event;

import org.example.socialnetworkfx.socialnetworkfx.domain.Friendship;
import org.example.socialnetworkfx.socialnetworkfx.domain.User;

public class FriendshipEntityChange extends jdk.jfr.Event implements Event{
    private ChangeEventType type;
    private Friendship data, oldData;

    public FriendshipEntityChange(ChangeEventType type, Friendship data) {
        this.type = type;
        this.data = data;
    }
    public FriendshipEntityChange(ChangeEventType type, Friendship data, Friendship oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Friendship getData() {
        return data;
    }

    public Friendship getOldData() {
        return oldData;
    }
}

