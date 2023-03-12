package com.example.restservice;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.concurrent.atomic.AtomicLong;

@RestController
public class greetingRequest {

    private String template="Hi, %s";
    private AtomicLong cnt=new AtomicLong();

    @GetMapping("/greeting")
    public Greeting greeting(@RequestParam(value="name",defaultValue="World") String name){
        return new Greeting(cnt.incrementAndGet(),String.format(template,name));
    }

}
