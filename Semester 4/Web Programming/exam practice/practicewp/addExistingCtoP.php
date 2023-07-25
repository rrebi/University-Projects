<?php
require_once 'db.php';
session_start(); // Start the session

// Check if the parent is logged in (session is set)
if (!isset($_SESSION['parent_id'])) {
    die("Parent not logged in.");
}

// Get the parent ID from the session
$parent_name = $_SESSION['username'];
$parent_id = $_SESSION['parent_id'];

// Check if the form has been submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get the child ID from the form
    $child_id = $_POST['child_id'];

    // Check if the child already has the selected parent
    // $query = "SELECT idP FROM child WHERE id = $child_id";
    // $result = $conn->query($query);

    // if ($result && $result->num_rows > 0) {
    //     $row = $result->fetch_assoc();
    //     $existing_parent_id = $row['idP'];

    //     if ($existing_parent_id == $parent_id) {
    //         // Child already has the selected parent, update the date to today
    //         $query = "UPDATE child SET date = CURDATE() WHERE id = $child_id";
    //         $result = $conn->query($query);

    //         if ($result) {
    //             echo "Child assigned successfully.";
    //         } else {
    //             echo "Failed to assign child.";
    //         }

    //         exit; // Stop further execution of the code
    //     }
    // }
    // Perform the assignment process (e.g., update the parent ID for the child record in the database)
    // ... (Database connection and query code)

    $query = "UPDATE child SET idP = $parent_id WHERE id = $child_id";
    $result = $conn->query($query);

    if ($result) {
        echo "Child assigned successfully.";
    } else {
        echo "Failed to assign child.";
    }
}
?>


<!DOCTYPE html>
<html>
<head>
    <title>Assign Child to Parent</title>
</head>
<body>
    <h1>Assign Child to Parent <?php echo $parent_name . " (ID: " . $parent_id . ")"; ?></h1>
    <form action="" method="post">
        <label for="child_id">Select Child:</label>
        <select id="child_id" name="child_id">
            <!-- Populate the dropdown with child options -->
            <?php
            // Retrieve child records from the database
            $query = "SELECT id, string, idP FROM child";
            $result = $conn->query($query);

            if ($result->num_rows > 0) {
                while ($row = $result->fetch_assoc()) {
                    $childId = $row['id'];
                    $childString = $row['string'];
                    $parentId = $row['idP'];
                    echo "<option value='$childId'>String: $childString, Parent ID: $parentId</option>";
                }
            }
            ?>
        </select>
        <br>
        <input type="submit" value="Assign Child">
    </form>
</body>
</html>
