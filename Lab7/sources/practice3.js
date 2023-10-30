function index() {window.location.href = "index.html"};

function validatePasswords() {
    first = document.getElementById("first").value;
    second = document.getElementById("second").value;

    if (first != second) alert("Passwords must match!")
    else if (first.length < 8 || second.length < 8) alert("Password must be at least 8 characters long")
    else alert("Passwords matched!");
}