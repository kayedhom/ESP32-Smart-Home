const char motorControlHeader_1[]  PROGMEM = R"header1(
<!DOCTYPE html>
<html>
<head>
<title> ESP32 Motor Control</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
* {box-sizing: border-box}
.table{
    width:100%;
    display:table;
}
.table-Control{
    width:100%;
    display:table;
    margin:20px
}

.row{
    display:table-row;
}

.fixedCell {
    width:15%;
    display:table-cell;

}

/* Style for generic cells */
.cell {
    display: table-cell;
    background: #72c3dc; /* Light blue background color */
    padding: 10px; /* Add some padding for spacing */
    border-radius: 5px; /* Add rounded corners */
    box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); /* Add a subtle shadow for depth */
}

.container {
    display: inline-block;
    justify-content: space-between; /* Distribute space evenly between children */
    align-items: center; /* Center items vertically */
    padding: 10px 100px; /* Add padding for spacing */

}

.progress_bar {
  font-size: 14px;  
  text-align: right;
  padding: 8px;
  color: white;
  background-color: #f0f0f0; /* Fallback color */
  background-image: linear-gradient(to right, #d0e0e3, #a2c4c9 , #76a5af ,#3d85c6); /* Gradient background */
  float:left;
  border-radius: 5px; /* Add rounded corners */
  box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); /* Add a subtle shadow for depth */
  height: 50px;
}


.Status_bar {
    text-align: right;
    padding: 10px 20px;
    color: #444444;
    float: left;
    background-image: linear-gradient(to right, #fff2cc, #e69138, #f9cb9c); /* Gradient background */
    border-radius: 5px; /* Add rounded corners */
    box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); /* Add a subtle shadow for depth */
    font-size: calc(0.8em + 0.8vw); /* Dynamic font size based on width and viewport width */
    white-space: nowrap; /* Prevent text from wrapping */

}


/* Style for button container */
.buttonsDiv {
    display: flex;
    justify-content: center; /* Center align buttons horizontally */
    align-items: center; /* Center align buttons vertically */
    margin-top: 20px; /* Add some spacing above the buttons */
}

/* Style for buttons */
.buttonsDiv button {
    background-color: #4CAF50; /* Green background color */
    color: white;
    border: none;
    border-radius: 5px; /* Add rounded corners */
    padding: 10px 20px; /* Add padding for spacing */
    margin: 0 10px; /* Add some spacing between buttons */
    cursor: pointer; /* Change cursor to pointer on hover */
    transition: background-color 0.3s; /* Add smooth transition for background color change */
}

/* Hover effect for buttons */
.buttonsDiv button:hover {
    background-color: #45a049; /* Darken background color on hover */
}

.startStop {
    font-size: 20px;
    background-color: #f44336;
    color: #ffffff;
    border: none;
    border-radius: 5px;
    padding: 10px 20px;
    margin: 0 10px; /* Add margin to create space between buttons */
    cursor: pointer;
    transition: background-color 0.3s;
    text-decoration: none;
    display: inline-flex; /* Use flexbox */
    align-items: center; /* Align items vertically */
}

.startStop:hover {
    background-color: #e74c3c; /* Darken background color on hover */
    border-color: #e74c3c; /* Darken border color on hover */
}

.ONoff {
    font-size: 20px;
    background-color: #f44336;
    color: #ffffff;
    border: none;
    border-radius: 5px;
    padding: 0px 20px;
    margin: 0 10px; /* Add margin to create space between buttons */
    cursor: pointer;
    transition: background-color 0.3s;
    text-decoration: none;
    display: inline-flex; /* Use flexbox */
    align-items: center; /* Align items vertically */
}

.ONoff:hover {
    background-color: #e74c3c; /* Darken background color on hover */
    border-color: #e74c3c; /* Darken border color on hover */
}

)header1";



const char motorControlHeader_2[] PROGMEM = R"P2( 


/* Style for navigation links */
.nextprev a.rj-right,
.nextprev a.rj-left {
    background-color: #FF7043; /* Reddish-orange background color */
    color: #ffffff; /* White text color */
    border-color: #FF7043; /* Reddish-orange border color */
    padding: 10px 20px; /* Add padding for spacing */
    border-radius: 5px; /* Add rounded corners */
    text-decoration: none; /* Remove default underline */
    transition: background-color 0.3s, color 0.3s, border-color 0.3s; /* Add smooth transition */
}

/* Hover effect for navigation links */
.nextprev a.rj-right:hover,
.nextprev a.rj-left:hover {
    background-color: #E57373; /* Lighter red background color on hover */
    border-color: #E57373; /* Lighter red border color on hover */
}

/* Style for buttons */
.rj-btn,
.rj-button {
    border: none; /* Remove border */
    display: inline-block; /* Display as inline-block */
    padding: 5px 10px; /* Add padding for spacing */
    border-radius: 5px; /* Add rounded corners */
    text-decoration: none; /* Remove default underline */
    color: #ffffff; /* White text color */
    background-color: #FF7043; /* Reddish-orange background color */
    cursor: pointer; /* Change cursor to pointer on hover */
    transition: background-color 0.3s; /* Add smooth transition */
    margin: 5px; /* Add margin for spacing */
    text-align: center; /* Center align text */
}

/* Hover effect for buttons */
.rj-btn:hover,
.rj-button:hover {
    background-color: #E57373; /* Lighter red background color on hover */
}


/* Add background color with gradient */
body {
    background-color: #f0f0f0; /* Fallback color */
    background-image: linear-gradient(to right, #ffcccc, #e6ccff); /* Gradient background */
    background-repeat: no-repeat;
    background-attachment: fixed; /* Keep background fixed while scrolling */
    font-family: 'Arial', sans-serif; /* Change font family for better readability */
    color: #333; /* Set default text color */
    margin: 0; /* Remove default margin for full-width background */
    padding: 0; /* Remove default padding */

}

/* Optional: Add styling for specific sections or elements within the body */
h1 {
    font-size: 1.5em; /* Increase font size for headings */
    margin-bottom: 20px; /* Add spacing below headings */
    text-align: center; /* Center align headings */
    text-transform: uppercase; /* Convert heading text to uppercase */
}

p {
    font-size: 1.2em; /* Increase font size for paragraphs */
    line-height: 1.6; /* Improve line spacing for better readability */
    text-align: center; /* Center align paragraphs */
}

/* Additional CSS styles */

</style>
</head>
<body>

<h1>ESP32 Smart Home</h1>)P2";


////////////////for motor 1 part 1///////////////
const char motor1Control_p1[] PROGMEM = R"P3(
<h2>Fan Controller</h2>
<div class="table">
    <div class="row">
        <div class="fixedCell">
            <div class="nextprev">
            <a class="rj-left rj-btn" href="/speed?do=m1slower">Slower</a>
            </div>        

        </div><!--fixedCell -->


        <div class="progress_bar bar1">)P3";


////////////////for motor 1 part 2///////////////
const char motor1Control_p2[] PROGMEM = R"P4(%</strong></div> 

        <div class="fixedCell">
        
          <div class="nextprev">       
          <a class="rj-right rj-btn" href="/speed?do=m1faster">Faster</a>
          </div>       

        </div><!--fixedCell -->
    </div><!--row -->


</div><!--table -->
<hr align="center" width="50%">
<div class="table">
    <div class="row">
        <div class="fixedCell">
            <div class="nextprev">
            <a class="rj-left rj-btn" href="/direction?dir=m1CCW">CCW</a>
            </div>        

        </div><!--fixedCell -->


        <div class="buttonsDiv">
            <a class="startStop" href="/stop?do=)P4";
            
 ////////////////for motor 1 part 3///////////////           
const char motor1Control_p3[] PROGMEM = R"P5(            
            </a>
        </div> 

        <div class="fixedCell">
        
          <div class="nextprev">       
          <a class="rj-right rj-btn" href="/direction?dir=m1CW">CW</a>
          </div>       

        </div><!--fixedCell -->
    </div><!--row - ESP.com -->


</div><!-- ---- table motor 1 ended -->)P5";

///////////////// motor 1 end******************************************
///////////////////////*************************************

////////////////for Led1///////////////


////////////////for Led part 1///////////////
const char Switch_one_control_p1[] PROGMEM = R"P3(
<!-- ---- Led started here ---- -->
<h2>Home Devices </h2>

<div class="table-Control">
    <div class="row">

        <div class="fixedCell">
         <div class="Status_bar bar2">)P3";


////////////////for Led part 2///////////////
const char Switch_one_control_p2[] PROGMEM = R"P4(</strong></div> 


        </div><!--fixedCell -->

              <div class="buttonsDiv">

                <a class="ONoff" href="/stop?do=)P4";
            
 ////////////////for Led part 3///////////////           
const char Switch_one_control[] PROGMEM = R"P5(            
                </a>
              </div> 

    </div><!--row - ESP.com -->
</div><!--table-Control -->)P5";

/*LED1 Ends*/

/*LED2 Starts*/
const char Switch_two_control_p1[] PROGMEM = R"P6(

<div class="table-Control">
    <div class="row">

        <div class="fixedCell">
         <div class="Status_bar bar2">)P6";


////////////////for Led part 2///////////////
const char Switch_two_control_p2[] PROGMEM = R"P7(</strong></div> 


        </div><!--fixedCell -->

              <div class="buttonsDiv">

                <a class="ONoff" href="/stop?do=)P7";
            
 ////////////////for Led part 3///////////////           
const char Switch_two_control[] PROGMEM = R"P8(            
                </a>
              </div> 

    </div><!--row - ESP.com -->
</div><!--table-Control -->

)P8";


const char CounterStartContainer[] PROGMEM = R"P9(            
<div class="table-Control">
    <div class="row">
    
    )P9";

const char Counter[] PROGMEM = R"P10(            
<div class="buttonsDiv">
    <a class="startStop" href="/stop?do=)P10";


const char ResetCounter[] PROGMEM = R"P10(            
<div class="nextprev">
    <a class="rj-left rj-btn" href="/stop?do=)P10";


const char CounterEndContainer[] PROGMEM = R"P11(            
    </div><!--row - ESP.com -->
</div><!--table-Control -->
)P11";









/*LED2 ENDS*/
////End leds