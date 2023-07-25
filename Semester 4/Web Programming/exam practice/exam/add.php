<?php
require_once 'db.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $name = $_POST['name'];
    $powers = $_POST['powers'];

    $stmt = $conn->prepare("INSERT INTO superhero (name, powers) VALUES (?, ?)");
    
    $stmt->bind_param("ss", $name, $powers);
    $stmt->execute();

    if ($stmt->affected_rows > 0) {
        echo "Superhero added successfully!";
    } else {
        echo "Failed to add superhero.";
    }

    $stmt->close();
}
$conn->close();
?>


<!DOCTYPE html>
<html>
<head>
    <title>Add Superhero</title>
</head>
<body>
    <h1>Add Superhero</h1>
    <form action="" method="post">
        <label for="name">Name:</label>
        <input type="text" id="name" name="name" required><br><br>
        
        <label for="powers">Powers:</label>
        <input type="text" id="powers" name="powers" required>
        
        <input type="submit" value="Add Superhero">
    </form>

    <a href="index.php">Menu</a>
</body>
</html>
