package org.example.socialnetworkfx.socialnetworkfx.utils.paging;

public class Page<T> {
    private Iterable<T> elementsOnPage;
    private int totalNumberOfElements;

    public Page(Iterable<T> elementsOnPage, int totalNumberOfElements) {
        this.elementsOnPage = elementsOnPage;
        this.totalNumberOfElements = totalNumberOfElements;
    }

    public Iterable<T> getElementsOnPage() {
        return elementsOnPage;
    }

    public int getTotalNumberOfElements() {
        return totalNumberOfElements;
    }
}
