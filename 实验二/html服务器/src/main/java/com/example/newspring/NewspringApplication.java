package com.example.newspring;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.jdbc.DataSourceAutoConfiguration;

//本身是spring的一个主键
//程序的主入口
@SpringBootApplication(exclude = DataSourceAutoConfiguration.class)
public class NewspringApplication {

    public static void main(String[] args) {
        SpringApplication.run(NewspringApplication.class, args);
    }

}
