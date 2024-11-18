package org.example.socialnetworkfx.socialnetworkfx.domain;

import java.util.Objects;

public class Tuple<E1, E2> {
    private E1 firstElement;
    private E2 secondElement;

    public Tuple(E1 firstElement, E2 secondElement) {
        this.firstElement = firstElement;
        this.secondElement = secondElement;
    }

    public E1 getFirstElement() {
        return firstElement;
    }

    public void setFirstElement(E1 firstElement) {
        this.firstElement = firstElement;
    }

    public E2 getSecondElement() {
        return secondElement;
    }

    public void setSecondElement(E2 secondElement) {
        this.secondElement = secondElement;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Tuple<?, ?> tuple = (Tuple<?, ?>) o;
        return Objects.equals(firstElement, tuple.firstElement) && Objects.equals(secondElement, tuple.secondElement);
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstElement, secondElement);
    }
}
