package com.example.schedulingtasks;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

import java.text.SimpleDateFormat;
import java.util.Date;

@Component
public class Timer {

    @Scheduled(fixedRate=2000)
    public void reportit(){
        System.out.println("opa");
    }

}
