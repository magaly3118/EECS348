function index() {window.location.href = "index.html"};

function stylize() {
    // get paragraph element
    let paragraph = document.querySelector("p");

    // set new border width, if applicable
    let borderWidth = document.getElementById("BorderWidth").value;
    if (borderWidth) paragraph.style.borderWidth = borderWidth + 'px';

    // set new border color, if applicable
    let borderColor = [];
    ["BorderR", "BorderG", "BorderB"].forEach(borderX =>{ 
        borderColor.push(document.getElementById(borderX).value);
    });

    if (borderColor.every(x => x !== "")) {
        paragraph.style.borderColor = `rgb(${borderColor[0]}, ${borderColor[1]}, ${borderColor[2]})`;
    }

    // set new background color, if applicable
    let backgroundColor = [];
    ["BackgroundR", "BackgroundG", "BackgroundB"].forEach(backgroundX =>{ 
        backgroundColor.push(document.getElementById(backgroundX).value);
    });

    if (backgroundColor.every(x => x !== "")) {
        paragraph.style.backgroundColor = `rgb(${backgroundColor[0]}, ${backgroundColor[1]}, ${backgroundColor[2]})`;
    }
}