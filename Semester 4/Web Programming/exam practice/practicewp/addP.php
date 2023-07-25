<?php
// Include the db.php file to establish a database connection
require_once 'db.php';

// Check if the form is submitted
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Retrieve form data
    $username = $_POST['username'];
    $password = $_POST['password'];
    $dob = $_POST['dob'];

    // Prepare and execute the SQL query to insert data into the parent table
    $stmt = $conn->prepare("INSERT INTO parent (username, password, dob) VALUES (?, ?, ?)");
    $stmt->bind_param("sss", $username, $password, $dob);
    $stmt->execute();

    // Check if the query was successful
    if ($stmt->affected_rows > 0) {
        echo "Parent added successfully!";
    } else {
        echo "Failed to add parent.";
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
    <title>Add Parent</title>
    <script>
        function togglePasswordVisibility() {
            var passwordField = document.getElementById("password");
            var toggleButton = document.getElementById("toggleButton");
            
            if (passwordField.type === "password") {
                passwordField.type = "text";
                toggleButton.textContent = "Hide Password";
            } else {
                passwordField.type = "password";
                toggleButton.textContent = "Show Password";
            }
        }
    </script>
</head>
<body>
    <h1>Add Parent</h1>
    <form action="" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required>
        <button type="button" id="toggleButton" onclick="togglePasswordVisibility()">Show Password</button><br><br>
        
        <label for="dob">Date of Birth:</label>
        <input type="date" id="dob" name="dob"  value="<?php echo date('Y-m-d'); ?>" required><br><br>
        
        <input type="submit" value="Add Parent">
    </form>

    <a href="index.php">Menu</a>
</body>
</html>
