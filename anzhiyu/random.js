var posts=["2025/04/20/uniapp开发指南/","2025/04/21/uniapp-login-register/"];function toRandomPost(){
    pjax.loadUrl('/'+posts[Math.floor(Math.random() * posts.length)]);
  };