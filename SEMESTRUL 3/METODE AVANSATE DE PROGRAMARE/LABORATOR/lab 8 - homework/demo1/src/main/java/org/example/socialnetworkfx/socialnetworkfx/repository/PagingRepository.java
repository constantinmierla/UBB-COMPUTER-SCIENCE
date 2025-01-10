package org.example.socialnetworkfx.socialnetworkfx.repository;

import org.example.socialnetworkfx.socialnetworkfx.domain.Entity;
import org.example.socialnetworkfx.socialnetworkfx.utils.paging.Page;
import org.example.socialnetworkfx.socialnetworkfx.utils.paging.Pageable;

public interface PagingRepository<ID,E extends Entity<ID>> extends Repository<ID ,E>{
    Page<E> findAllOnPage (Pageable pageable,ID id);

}
