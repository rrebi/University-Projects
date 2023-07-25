<?php
session_start();

// Check if the parent is already logged in
if (isset($_SESSION['parent_id'])) {
    
    $message = "Logged out successfully.";
    // Parent is logged in, log out
    session_unset();
    session_destroy();
    // header("Location: index.php");
    // exit();
    
    $message = "Logged out successfully.";
} else {
    // Parent is not logged in, you can display a message or perform any other actions
    //echo "Not logged in";
    
    $message = "Not logged in.";
}

$_SESSION['notification'] = $message;

// Redirect to index.php
header("Location: index.php");
exit();
?>