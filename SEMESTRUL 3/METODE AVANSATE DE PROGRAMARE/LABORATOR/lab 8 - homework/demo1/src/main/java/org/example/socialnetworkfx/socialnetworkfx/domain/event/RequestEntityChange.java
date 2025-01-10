package org.example.socialnetworkfx.socialnetworkfx.domain.event;

import jdk.jfr.Event;
import org.example.socialnetworkfx.socialnetworkfx.domain.FriendshipRequest;

public class RequestEntityChange extends Event {
    private ChangeEventType type;
    private FriendshipRequest data, oldData;

    public RequestEntityChange(ChangeEventType type, FriendshipRequest data) {
        this.type = type;
        this.data = data;
    }


    public RequestEntityChange(ChangeEventType type, FriendshipRequest data, FriendshipRequest oldData) {
        this.type = type;
        this.data = data;
        this.oldData = oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public FriendshipRequest getData() {
        return data;
    }

    public FriendshipRequest getOldData() {
        return oldData;
    }
}
