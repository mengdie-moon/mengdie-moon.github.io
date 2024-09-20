\self.addEventListener('install', event => {
    event.waitUntil(
        caches.open('v1').then(cache => {
            return cache.addAll([
                '/',
                '/uptime.js',
                '/style.css', 
            ]);
        })
    );
});
self.addEventListener('fetch', event => {
    event.respondWith(
        caches.match(event.request).then(response => {
            return response || fetch(event.request);
        })
    );
});

setInterval(() => {
    totalSeconds++;
    localStorage.setItem('totalSeconds', totalSeconds.toString());
}, 1000);