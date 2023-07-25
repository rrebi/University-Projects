<?php
// Include the db.php file to establish a database connection
require_once 'db.php';
session_start();

// Check if the parentID exists in the session
if (!isset($_SESSION['parent_id'])) {
    $error_message = "Parent ID not found in the session. Please log in as a parent.";
    header("Location: login.php?error=" . urlencode($error_message));
    exit; // Stop further execution of the code
}


// Check if the form is submitted
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Retrieve form data
    $string = $_POST['string'];
    $number = $_POST['number'];
    
    // Retrieve the parent ID from the session (assuming you have stored it there)
    $parentID = $_SESSION['parent_id']; 

    // Get the current date
    //$date = date("Y-m-d");

    $date = date("Y-m-d H:i:s");

    // Prepare and execute the SQL query to insert data into the child table
    $stmt = $conn->prepare("INSERT INTO child (idP, string, date, number) VALUES (?, ?, ?, ?)");
    $stmt->bind_param("ssss", $parentID, $string, $date, $number);
    $stmt->execute();

    // Check if the query was successful
    if ($stmt->affected_rows > 0) {
        echo "Child added successfully!";
    } else {
        echo "Failed to add child.";
    }

    // Close the statement
    $stmt->close();
}

// Close the database connection
$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Add Child</title>
</head>
<body>
    <h1>Add Child</h1>
    <form action="" method="post">

        <label for="string">String:</label>
        <input type="text" id="string" name="string" required><br><br>
        
        <label for="number">Number:</label>
        <input type="number" id="number" name="number" required>
        
        <input type="submit" value="Add Child">
    </form>

    <a href="index.php">Back to Home</a>

</body>
</html>
