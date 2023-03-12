package com.example.accessingdataneo4j;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.data.neo4j.repository.config.EnableNeo4jRepositories;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@SpringBootApplication
@EnableNeo4jRepositories
public class AccessingDataNeo4jApplication {

	private final static Logger log = LoggerFactory.getLogger(AccessingDataNeo4jApplication.class);

	public static void main(String[] args) {
		SpringApplication.run(AccessingDataNeo4jApplication.class, args);
	}



	@Bean
	CommandLineRunner demo(PersonRepository personRepository) {
		return args -> {

			personRepository.deleteAll();

			Person greg = new Person("Greg");
			Person roy = new Person("Roy");
			Person craig = new Person("Craig");

			List<Person> team = Arrays.asList(greg, roy, craig);

			personRepository.save(greg);
			personRepository.save(roy);
			personRepository.save(craig);

			log.info("Before linking up with Neo4j...");

			team.stream().forEach(person -> log.info("\t" + person.toString()));


			greg = personRepository.findByName(greg.getName());
			greg.teammates=personRepository.findByTeammatesName(greg.getName());
			greg.worksWith(roy);
			personRepository.save(greg);

			greg = personRepository.findByName(greg.getName());
			greg.teammates=personRepository.findByTeammatesName(greg.getName());
			greg.worksWith(craig);
			personRepository.save(greg);

			roy = personRepository.findByName(roy.getName());
			roy.teammates=personRepository.findByTeammatesName(roy.getName());
			roy.worksWith(craig);
			personRepository.save(roy);

			// We already know craig works with roy and greg
			craig = personRepository.findByName(craig.getName());
			craig.teammates=personRepository.findByTeammatesName(craig.getName());
			craig.worksWith(roy);
			personRepository.save(craig);

			List<Person>pom=new ArrayList<>();
			pom.add(greg);
			pom.add(roy);
			pom.add(craig);
			for(Person p:pom){
				p=personRepository.findByName(p.getName());
				p.teammates=personRepository.findByTeammatesName2(p.getName());
				System.out.println(p.toString());
			}


		};
	}

}
