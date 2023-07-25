<?php
session_start();

// Check if the form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {

    $_SESSION["role"] = "visitor";

    header("Location: addnews.html");
    exit();
}
?>
