package org.example.socialnetworkfx.socialnetworkfx.utils;

import jdk.jfr.Event;

public interface Observer<E extends Event> {
    void update(E e);
}