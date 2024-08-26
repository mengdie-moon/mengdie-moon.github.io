// 监听install事件
self.addEventListener('install', event => {
    // 缓存一些资源
    event.waitUntil(
        caches.open('v1').then(cache => {
            return cache.addAll([
                '/',
                '/uptime.js',
                '/style.css', // 假设你有一个样式文件
                // 其他需要缓存的资源
            ]);
        })
    );
});

// 监听fetch事件
self.addEventListener('fetch', event => {
    event.respondWith(
        caches.match(event.request).then(response => {
            return response || fetch(event.request);
        })
    );
});

// 每秒更新一次运行时间
setInterval(() => {
    totalSeconds++;
    localStorage.setItem('totalSeconds', totalSeconds.toString());
}, 1000);