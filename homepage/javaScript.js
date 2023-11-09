// create element by ids
let addButton = document.getElementById('add');
let toAddContainer = document.getElementById('toAddContainer');
let inputField = document.getElementById('inputField');

// add a click event to add button
addButton.addEventListener('click', function() {
    var paragraph = document.createElement('p');

    // css class to text
    paragraph.classList.add("paragraph-styling");
    paragraph.innerText = inputField.value;

    // append to the list
    toAddContainer.appendChild(paragraph);

    // clear input field after adding
    inputField.value = "";

    // Add a click event, When clicked add the acc to list
    paragraph.addEventListener('click', function() {
        paragraph.style.textDecoration = "line-through";
    })
    // double-click event for list acc, When double-clicked remove the acc in list
    paragraph.addEventListener("dblclick", function() {
        toAddContainer.removeChild(paragraph);
    })
})