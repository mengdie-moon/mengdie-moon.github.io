var posts=["2025/04/20/uniapp开发指南/","2025/04/21/uniapp登录注册页面开发实战/","2025/04/26/搭建属于你的免费博客!/"];function toRandomPost(){
    pjax.loadUrl('/'+posts[Math.floor(Math.random() * posts.length)]);
  };