import React from "react";
import { database } from "./firebase";
import { ref, set } from "firebase/database";
import './App.css'; // Import the CSS file

function App() {
  const updateLED = (color) => {
    set(ref(database, 'light/led'), color)
    .then(() => {
      console.log(`LED updated to ${color}`);
    })
    .catch((error) => {
      console.error("Error updating LED:", error);
    });
  };

  return (
    <div className="App">
      <h1>Control the LED</h1>
      <div className="button-container">
        <button className="led-button red" onClick={() => updateLED("RED")}>Red</button>
        <button className="led-button yellow" onClick={() => updateLED("YELLOW")}>Yellow</button>
        <button className="led-button green" onClick={() => updateLED("GREEN")}>Green</button>
      </div>
    </div>
  );
}

export default App;
