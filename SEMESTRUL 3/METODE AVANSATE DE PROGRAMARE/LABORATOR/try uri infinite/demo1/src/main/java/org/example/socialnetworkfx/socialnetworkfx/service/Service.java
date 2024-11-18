package org.example.socialnetworkfx.socialnetworkfx.service;

public interface Service<E> {
    E delete(Long ID);
    Iterable<E> findAll();

}
