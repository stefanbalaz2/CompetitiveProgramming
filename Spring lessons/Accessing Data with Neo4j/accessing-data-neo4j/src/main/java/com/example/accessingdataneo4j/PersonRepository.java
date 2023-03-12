package com.example.accessingdataneo4j;

import ch.qos.logback.core.joran.sanity.Pair;
import org.springframework.data.neo4j.repository.Neo4jRepository;
import org.springframework.data.neo4j.repository.query.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;
import java.util.Set;


public interface PersonRepository extends Neo4jRepository<Person,Long> {

    @Query("MATCH (p:Person) WHERE p.name=$name RETURN p")
    Person findByName(@Param("name")String name);
    @Query("MATCH (n:Person)-[:tmt]->(m) WHERE n.name = $ime RETURN COLLECT(m)")
    Set<Person> findByTeammatesName(@Param("ime") String name);

    @Query("MATCH (n:Person)-[:tmt]-(m) WHERE n.name = $ime RETURN COLLECT(m)")
    Set<Person> findByTeammatesName2(@Param("ime") String name);

    ///Person findByName(String name);
    ///List<Person> findByTeammatesName(String name);
}
