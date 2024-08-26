function encryptMd5() {
    const inputText = document.getElementById('inputText').value;
    if (!inputText) {
        alert('请输入文本');
        return;
    }

    const encoder = new TextEncoder();
    const data = encoder.encode(inputText);
    const hashBuffer = crypto.subtle.digest('MD5', data);

    hashBuffer.then(hashArray => {
        const hashHex = Array.from(hashArray).map(b => b.toString(16).padStart(2, '0')).join('');
        document.getElementById('md5Result').textContent = hashHex;
    }).catch(err => {
        console.error(err);
    });
}

// Base64加密
function base64Encode(str) {
    return btoa(unescape(encodeURIComponent(str)));
}

// Base64解密
function base64Decode(str) {
return decodeURIComponent(escape(atob(str)));
}

// 加密按钮点击事件
function encrypt() {
var input = document.getElementById('inputText').value;
var output = base64Encode(input);
document.getElementById('outputText').value = output;
}

// 解密按钮点击事件
function decrypt() {
var input = document.getElementById('inputText').value;
var output = base64Decode(input);
document.getElementById('outputText').value = output;
}

//密码生成
function generatePassword() {
    const length = document.getElementById('length').value;
    const includeUpperCase = document.getElementById('uppercase').checked;
    const includeLowerCase = document.getElementById('lowercase').checked;
    const includeNumbers = document.getElementById('numbers').checked;
    const includeSymbols = document.getElementById('symbols').checked;

    const uppercaseChars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
    const lowercaseChars = 'abcdefghijklmnopqrstuvwxyz';
    const numberChars = '0123456789';
    const symbolChars = '!@#$%^&*()_+-=[]{}|;:,.<>?';

    let chars = '';
    if (includeUpperCase) chars += uppercaseChars;
    if (includeLowerCase) chars += lowercaseChars;
    if (includeNumbers) chars += numberChars;
    if (includeSymbols) chars += symbolChars;

    if (chars.length === 0) {
        alert('请至少选择一种字符类型。');
        return '';
    }

    let password = '';
    for (let i = 0; i < length; i++) {
        password += chars.charAt(Math.floor(Math.random() * chars.length));
    }
    return password;
}

function copyToClipboard(text) {
    const elem = document.createElement("textarea");
    document.body.appendChild(elem);
    elem.value = text;
    elem.select();
    document.execCommand("copy");
    document.body.removeChild(elem);
    alert("密码已复制到剪贴板！");
}

//时间戳
function convertTimestampToDateTime() {
    const timestampInput = document.getElementById('timestampInput');
    const timestamp = parseInt(timestampInput.value);
  
    if (!timestamp || timestamp <= 0) {
      alert('请输入有效的UNIX时间戳。');
      return;
    }
  
    const date = new Date(timestamp * 1000); // 转换为毫秒
    const dateString = date.getFullYear() + '-' +
        ('0' + (date.getMonth() + 1)).slice(-2) + '-' +
        ('0' + date.getDate()).slice(-2) + ' ' +
        ('0' + date.getHours()).slice(-2) + ':' +
        ('0' + date.getMinutes()).slice(-2) + ':' +
        ('0' + date.getSeconds()).slice(-2);

    document.getElementById('dateTimeOutput').value = dateString;
    }

    function convertDateTimeToTimestamp() {
    const dateInput = document.getElementById('dateInput');
    const date = new Date(dateInput.value);

    if (isNaN(date.getTime())) {
        alert('请输入有效的日期和时间。');
        return;
    }

    const timestamp = Math.floor(date.getTime() / 1000); // 转换为秒
    document.getElementById('timestampOutput').value = timestamp;
}
