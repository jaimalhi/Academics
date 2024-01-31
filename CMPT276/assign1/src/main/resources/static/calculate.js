let grades = [65.95, 56.98, 78.62, 96.1, 90.3, 72.24, 92.34, 60.00, 81.43, 86.22, 88.33, 9.03,
    49.93, 52.34, 53.11, 50.10, 88.88, 55.32, 55.69, 61.68, 70.44, 70.54, 90.0, 71.11, 80.01];

// HTML elements + vars
var btn = document.getElementById("submit");
var gradeInput = document.getElementById("inputNum");
var helperText = document.querySelectorAll("#helperText");
var inputs = document.querySelectorAll(".gradeNum"); 
var values;

// get values from bounds list
function getNumericValues() { 
    //values = [ 100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 0 ]
    values = Array.from(inputs).map(input => parseFloat(input.value));
}

// Handle bounds of letter grades overlapping
for(let i = 0; i < inputs.length-1; i++){
    inputs[i].addEventListener('input', () => {
        var newValue = parseFloat(inputs[i].value);
        if(i == 0){ //first element
            if (newValue > inputs[i+1].value){
                drawHistogram();
                helperText[0].classList.add("invisible");
            } else {
                helperText[0].classList.remove("invisible");
            }
        } else {
            console.log('New value:', newValue);
            console.log(inputs[i+1].value);
            console.log(inputs[i-1].value);
            if (newValue > inputs[i+1].value && newValue < inputs[i-1].value){
                helperText[0].classList.add("invisible");
                drawHistogram();
            } else {
                helperText[0].classList.remove("invisible");
            }
        }
    });
}

// Add event listener to submit btn so add new grade to grades array
btn.addEventListener("click", () => {
    // Get the value from the input field and parse it as a float
    let newGrade = parseFloat(gradeInput.value); 
    // Check if the input is a valid number in range
    if (!isNaN(newGrade) && (newGrade >= values[values.length-1] && newGrade <= values[0])) { 
        grades.push(newGrade); // Add the new grade to the grades array
        gradeInput.value = ""; // Clear the input field
        drawHistogram();
        helperText[1].classList.add("invisible");
    } else {
        helperText[1].classList.remove("invisible");
        gradeInput.value = ""; // Clear the input field
    }
});

// Displaying histogram
var a1Cell = document.getElementById("A1");
var a2Cell = document.getElementById("A2");
var a3Cell = document.getElementById("A3");
var b1Cell = document.getElementById("B1");
var b2Cell = document.getElementById("B2");
var b3Cell = document.getElementById("B3");
var c1Cell = document.getElementById("C1");
var c2Cell = document.getElementById("C2");
var c3Cell = document.getElementById("C3");
var dCell = document.getElementById("D");
var fCell = document.getElementById("F");

// define variables for all grades
var a1, a2, a3, b1, b2, b3, c1, c2, c3, d, f;
function countOccurrences() {
    a1 = a2 = a3 = b1 = b2 = b3 = c1 = c2 = c3 = d = f = 0;
    getNumericValues(); //get bounds
    for(let i = 0; i < grades.length; i++){
        if(grades[i] >= values[1]) a1++;      //95
        else if(grades[i] >= values[2]) a2++; //90
        else if(grades[i] >= values[3]) a3++; //85
        else if(grades[i] >= values[4]) b1++; //80
        else if(grades[i] >= values[5]) b2++; //75
        else if(grades[i] >= values[6]) b3++; //70
        else if(grades[i] >= values[7]) c1++; //65
        else if(grades[i] >= values[8]) c2++; //60
        else if(grades[i] >= values[9]) c3++; //55
        else if(grades[i] >= values[10]) d++; //50
        else f++;
    }
}

function drawHistogram(){
    countOccurrences();
    a1Cell.style.width = `${a1*2}rem`;
    a1Cell.innerHTML = a1;

    a2Cell.style.width = `${a2*2}rem`;
    a2Cell.innerHTML = a2;

    a3Cell.style.width = `${a3*2}rem`;
    a3Cell.innerHTML = a3;

    b1Cell.style.width = `${b1*2}rem`;
    b1Cell.innerHTML = b1;

    b2Cell.style.width = `${b2*2}rem`;
    b2Cell.innerHTML = b2;

    b3Cell.style.width = `${b3*2}rem`;
    b3Cell.innerHTML = b3;

    c1Cell.style.width = `${c1*2}rem`;
    c1Cell.innerHTML = c1;

    c2Cell.style.width = `${c2*2}rem`;
    c2Cell.innerHTML = c2;

    c3Cell.style.width = `${c3*2}rem`;
    c3Cell.innerHTML = c3;

    dCell.style.width = `${d*2}rem`;
    dCell.innerHTML = d;

    fCell.style.width = `${f*2}rem`;
    fCell.innerHTML = f;
}
drawHistogram(); //initial call