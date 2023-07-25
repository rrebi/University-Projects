<?php
require_once 'db.php';


if (isset($_GET['id'])) {
    $id = $_GET['id'];

    // Fetch the child from the database
    $stmt = $conn->prepare("SELECT * FROM child WHERE id = ?");
    $stmt->bind_param("i", $id);
    $stmt->execute();
    $result = $stmt->get_result();
    $child = $result->fetch_assoc();

    if (!$child) {
        // child with the given id doesn't exist
        echo "child not found.";
        exit();
    }
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Process the form submission

    // Retrieve updated data from the form
    $idP = $_POST['idP'];
    $string = $_POST['string'];
    $date = $_POST['date'];
    
    $number = $_POST['number'];

    // Update the child in the database
    $stmt = $conn->prepare("UPDATE child SET string = ?, date = ?, number=? WHERE id = ?");
    $stmt->bind_param("ssii", $string, $date, $number, $id);
    $stmt->execute();

    // Redirect back to the child list page
    header("Location: getAllC.php");
    exit();
}
?>

<!DOCTYPE html>
<html>
<head>
  <title>Update child</title>
</head>
<body>
  <h1>Update child</h1>
  <form method="POST">
    <label for="string">string:</label>
    <input type="text" id="string" name="string" value="<?php echo $child['string']; ?>"><br><br>

    <label for="date">Date:</label>
    <input type="date" id="date" name="date" value="<?php echo $child['date']; ?>"><br><br>
    
    <label for="number">Number:</label>
    <input type="number" id="number" name="number" value="<?php echo $child['number']; ?>"><br><br>

    <input type="submit" value="Update">
  </form>

  <!-- Confirmation message -->
  <p>Are you sure you want to update this child?</p>
  <a href="updateP.php?id=<?php echo $child['id']; ?>&confirm=true">Yes</a>
  | 
  <a href="getAllC.php">No</a>
</body>
</html>
