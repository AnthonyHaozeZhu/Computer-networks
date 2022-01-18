package com.example.newspring.controller;



import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;



@Controller
public class Hellocontroller {

    @RequestMapping("/index")
    public String login(){
            return "index";
        }

//    @RequestMapping(value = "/user/login", method = {RequestMethod.POST, RequestMethod.GET})
//    public String login(@RequestParam(value = "username") String username,
//                        @RequestParam(value = "password") String password,
//                        Model model, HttpSession session){
//        username = username.substring(0, username.indexOf('@'));
//        String Stuname = commonService.login(username, password);
//        if(Stuname != null){
//            session.setAttribute("loginUser", Stuname);
//            return "redirect:/main.html";
//        }
//        else {
//            model.addAttribute("msg","用户名或密码错误!");
//            return "index";
//        }
//    }
}
