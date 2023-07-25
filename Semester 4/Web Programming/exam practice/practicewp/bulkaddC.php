<?php
require_once 'db.php';
session_start();

// Check if the parentID exists in the session
if (!isset($_SESSION['parent_id'])) {
    $error_message = "Parent ID not found in the session. Please log in as a parent.";
    header("Location: login.php?error=" . urlencode($error_message));
    exit; // Stop further execution of the code
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $childData = $_POST['child'];
    $parentID = $_SESSION['parent_id'];

    $stmt = $conn->prepare("INSERT INTO child (idP, string, date, number) VALUES (?, ?, NOW(), ?)");

    foreach ($childData as $child) {
        $string = $child['string'];
        $number = $child['number'];

        $stmt->bind_param("sss", $parentID, $string, $number);
        $stmt->execute();
    }

    if ($stmt->affected_rows > 0) {
        echo "Children added successfully!";
    } else {
        echo "Failed to add children.";
    }

    $stmt->close();
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Add Child</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script>
        $(document).ready(function() {
            let childCount = 1;

            $('#add-child').click(function() {
                childCount++;

                let newChild = `
                    <div>
                        <h3>Child ${childCount}</h3>
                        <label>String:</label><br>
                        <input type="text" name="child[${childCount}][string]" required><br><br>
                        <label>Number:</label><br>
                        <input type="number" name="child[${childCount}][number]" required><br><br>
                    </div>
                `;

                $('#child-container').append(newChild);
            });
        });
    </script>
</head>
<body>
    <h1>Add Child</h1>
    <form method="POST" action="">
        <div id="child-container">
            <div>
                <h3>Child 1</h3>
                <label>String:</label><br>
                <input type="text" name="child[1][string]" required><br><br>
                <label>Number:</label><br>
                <input type="number" name="child[1][number]" required><br><br>
            </div>
        </div>
        <button type="button" id="add-child">Add More Children</button><br><br>
        <input type="submit" value="Submit">
    </form>
    <a href="index.php">Back to Home</a>
</body>
</html>
