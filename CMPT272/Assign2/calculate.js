const csvData = []; // Initialize an array to store the CSV data
const grades = []; // array to store grades alone for display

// HTML elements + vars
var btn = document.getElementById("submit");
var gradeInput = document.getElementById("inputNum");
var helperText = document.querySelectorAll("#helperText");
var inputs = document.querySelectorAll(".gradeNum");
var highest = document.getElementById("highest");
var lowest = document.getElementById("lowest");
var median = document.getElementById("median");
var mean = document.getElementById("mean");
var values;

// =========================== File input handling ===========================
function init() {
   document.getElementById("fileInput").addEventListener("change", handleFileSelect, false);
}

function handleFileSelect(event) {
   const reader = new FileReader();
   reader.onload = handleFileLoad; // call func upon successful load
   reader.readAsText(event.target.files[0]);
}

function handleFileLoad(event) {
   const fileContent = event.target.result;
   const lines = fileContent.split("\n"); // Split the CSV content into lines
   const headers = lines[0].trim().split(","); // get headers
   let lowestGrade = Number.MAX_VALUE; // 0
   let highestGrade = Number.MIN_VALUE; // 100

   // Iterate through the lines, starting from the second line (index 1)
   for (let i = 1; i < lines.length; i++) {
      const line = lines[i].trim();
      if (line === "") {
         // Skip empty lines
         continue;
      }
      const values = line.split(","); // Split the line into an array of values
      const rowData = {}; // object to represent a row

      // Iterate through the values and assign them
      for (let j = 0; j < headers.length; j++) {
         rowData[headers[j]] = values[j];
      }

      // Extract the name and grade from the row data
      const name = rowData["Name"];
      const grade = parseFloat(rowData["Percent"]); // Assuming 'Percent' is the column with grades

      grades.push(grade);
      // Check for the lowest and highest grades and update their respective names
      if (grade < lowestGrade) {
         lowestGrade = grade;
         lowest.innerHTML = `${name}(${grade}%)`;
      }
      if (grade > highestGrade) {
         highestGrade = grade;
         highest.innerHTML = `${name}(${grade}%)`;
      }

      csvData.push(rowData); // Add the row data object to array
   }
   calulateMeanMedian();
   drawHistogram();
   console.log(csvData);
}

function calulateMeanMedian() {
   // Calculate the mean (average) of the grades
   let gradeMean = grades.reduce((sum, grade) => sum + grade, 0) / grades.length;

   // To calculate the median sort the grades array
   const sortedGrades = grades.slice().sort((a, b) => a - b);
   let gradeMedian;

   if (sortedGrades.length % 2 === 0) {
      // If the number of grades is even, take the average of the middle two values
      const middleIndex = sortedGrades.length / 2;
      gradeMedian = (sortedGrades[middleIndex - 1] + sortedGrades[middleIndex]) / 2;
   } else {
      // If the number of grades is odd, take the middle value
      const middleIndex = Math.floor(sortedGrades.length / 2);
      gradeMedian = sortedGrades[middleIndex];
   }

   // Now you can log or use the mean and median values
   console.log("Mean:", gradeMean);
   mean.innerHTML = gradeMean.toFixed(2);
   console.log("Median:", gradeMedian);
   median.innerHTML = gradeMedian.toFixed(2);
}

// =========================== Grade Scale Handling ===========================

// get values from bounds list
function getNumericValues() {
   //values = [ 100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 0 ]
   values = Array.from(inputs).map((input) => parseFloat(input.value));
}

// Handle bounds of letter grades overlapping
const inputsArrSize = inputs.length;
for (let i = 0; i < inputsArrSize; i++) {
   inputs[i].addEventListener("input", () => {
      var newValue = parseFloat(inputs[i].value);
      if (i == 0) {
         //first element
         if (newValue > inputs[i + 1].value && newValue <= 100) {
            drawHistogram();
            helperText[0].classList.add("invisible");
         } else {
            helperText[0].classList.remove("invisible");
         }
      } else if (i == inputsArrSize - 1) {
         //last element
         if (newValue < inputs[i - 1].value && newValue >= 0) {
            drawHistogram();
            helperText[0].classList.add("invisible");
         } else {
            helperText[0].classList.remove("invisible");
         }
      } else {
         console.log("New value:", newValue);
         console.log(inputs[i + 1].value);
         console.log(inputs[i - 1].value);
         if (newValue > inputs[i + 1].value && newValue < inputs[i - 1].value) {
            helperText[0].classList.add("invisible");
            drawHistogram();
         } else {
            helperText[0].classList.remove("invisible");
         }
      }
   });
}

// =========================== Displaying histogram ===========================
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
   for (let i = 0; i < grades.length; i++) {
      if (grades[i] >= values[1]) a1++; //95
      else if (grades[i] >= values[2]) a2++; //90
      else if (grades[i] >= values[3]) a3++; //85
      else if (grades[i] >= values[4]) b1++; //80
      else if (grades[i] >= values[5]) b2++; //75
      else if (grades[i] >= values[6]) b3++; //70
      else if (grades[i] >= values[7]) c1++; //65
      else if (grades[i] >= values[8]) c2++; //60
      else if (grades[i] >= values[9]) c3++; //55
      else if (grades[i] >= values[10]) d++; //50
      else f++;
   }
}

function drawHistogram() {
   const barLength = 2;
   countOccurrences();

   a1Cell.style.width = `${a1 * barLength}rem`;
   a1Cell.innerHTML = a1;

   a2Cell.style.width = `${a2 * barLength}rem`;
   a2Cell.innerHTML = a2;

   a3Cell.style.width = `${a3 * barLength}rem`;
   a3Cell.innerHTML = a3;

   b1Cell.style.width = `${b1 * barLength}rem`;
   b1Cell.innerHTML = b1;

   b2Cell.style.width = `${b2 * barLength}rem`;
   b2Cell.innerHTML = b2;

   b3Cell.style.width = `${b3 * barLength}rem`;
   b3Cell.innerHTML = b3;

   c1Cell.style.width = `${c1 * barLength}rem`;
   c1Cell.innerHTML = c1;

   c2Cell.style.width = `${c2 * barLength}rem`;
   c2Cell.innerHTML = c2;

   c3Cell.style.width = `${c3 * barLength}rem`;
   c3Cell.innerHTML = c3;

   dCell.style.width = `${d * barLength}rem`;
   dCell.innerHTML = d;

   fCell.style.width = `${f * barLength}rem`;
   fCell.innerHTML = f;
}
