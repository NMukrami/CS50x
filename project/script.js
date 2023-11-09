// Jokes Page

// create var from HTML element
const button = document.querySelector('.container button');
const joke_text = document.querySelector('.container p');
const url = 'https://icanhazdadjoke.com/'

document.addEventListener('DOMContentLoaded', get_api)

// add click event
button.addEventListener('click', get_api);

// fun that call API
async function get_api() {
    try {
        // sending a "GET" request to the API
        const response = await fetch(url, {
            headers: {
                'Accept': 'application/json'
            }
        });

        // store response as JSON
        const text = await response.json();

        // print text joke in the paragraph element
        joke_text.innerHTML = text.joke;

        // catch any errors that may happen
    } catch (error) {
        // print error msg
        joke_text.innerHTML = 'Please try again later';
    }
}


// Submit Page

// create element by ids
let submit = document.getElementById('add');
let add_joke = document.getElementById('toAddContainer');
let input_field = document.getElementById('inputField');

// add a click event to add button
submit.addEventListener('click', function() {
    var paragraph = document.createElement('p');

    // css class to text
    paragraph.classList.add();
    paragraph.innerText = input_field.value;

    // append to the list
    add_joke.appendChild(paragraph);

    // clear input field after submit
    input_field.value = "";

    // Add a click event, When clicked add the list joke
    paragraph.addEventListener('click', function() {
        paragraph.style.textDecoration;
    })
    // double-click event, When double-clicked remove the list joke
    paragraph.addEventListener("dblclick", function() {
        add_joke.removeChild(paragraph);
    })
})
