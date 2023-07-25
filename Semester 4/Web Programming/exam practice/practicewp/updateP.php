<?php
require_once 'db.php';

if (isset($_GET['id'])) {
    $id = $_GET['id'];

    // Fetch the parent from the database
    $stmt = $conn->prepare("SELECT * FROM parent WHERE id = ?");
    $stmt->bind_param("i", $id);
    $stmt->execute();
    $result = $stmt->get_result();
    $parent = $result->fetch_assoc();

    if (!$parent) {
        // Parent with the given id doesn't exist
        echo "Parent not found.";
        exit();
    }
}


if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $id = $_GET['id'];
    $username = $_POST['username'];
    $dob = $_POST['dob'];

    // Update the parent in the database
    $stmt = $conn->prepare("UPDATE parent SET username = ?, dob = ? WHERE id = ?");
    $stmt->bind_param("ssi", $username, $dob, $id);
    $stmt->execute();

    // Return a response indicating success
    echo "success";
}
?>


<!DOCTYPE html>
<html>
<head>
    <title>Update Parent</title>
    <script>
        function confirmUpdate() {
            if (confirm("Are you sure you want to update this parent?")) {
                document.getElementById("updateForm").submit();
            }
        }
    </script>
</head>
<body>
    <h1>Update Parent</h1>
    <form method="POST" id="updateForm" action="">
        <label for="username">Name:</label>
        <input type="text" id="username" name="username" value="<?php echo $parent['username']; ?>"><br><br>

        <label for="dob">Date:</label>
        <input type="date" id="dob" name="dob" value="<?php echo $parent['dob']; ?>"><br><br>

        <button type="button" onclick="confirmUpdate()">Update</button>
        <a href="getAllP.php">Cancel</a>
    </form>
</body>
</html>
