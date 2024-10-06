// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
import { getDatabase } from "firebase/database";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
    apiKey: "AIzaSyDTwLmVpOGNTc71mDnN14mgE6GMwTrqQuw",
    databaseURL:"https://arduinotrafficcontrol-default-rtdb.asia-southeast1.firebasedatabase.app/",
    authDomain: "arduinotrafficcontrol.firebaseapp.com",
    projectId: "arduinotrafficcontrol",
    storageBucket: "arduinotrafficcontrol.appspot.com",
    messagingSenderId: "161932507489",
    appId: "1:161932507489:web:d64444048802d286c6ed20",
    measurementId: "G-EBD64PP96Y"
  };
// Initialize Firebase
const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

export{database};