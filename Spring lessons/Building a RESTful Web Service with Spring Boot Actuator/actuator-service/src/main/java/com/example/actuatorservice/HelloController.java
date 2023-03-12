package com.example.actuatorservice;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.concurrent.atomic.AtomicLong;

@Controller
public class HelloController {

    private String template="Hello, %s!";
    private AtomicLong id=new AtomicLong();

    @GetMapping("/hello-world")
    @ResponseBody
    public Greeting hello(@RequestParam(value = "name",required = false,defaultValue = "Stranger") String name){
        return new Greeting(id.incrementAndGet(),String.format(template,name));
    }

}
