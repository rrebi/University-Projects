<?php
session_start();

// Include the db.php file to establish a database connection
require_once 'db.php';

// Check if the parentID exists in the session
if (!isset($_SESSION['parent_id'])) {
    $error_message = "Parent ID not found in the session. Please log in as a parent.";
    header("Location: login.php?error=" . urlencode($error_message));
    exit; // Stop further execution of the code
}

// Check if the form is submitted
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Handle adding a child to the shopping basket
    if (isset($_POST['add_to_basket'])) {
        $childID = $_POST['child_id'];

        // Retrieve the child's string from the database
        $stmt = $conn->prepare("SELECT string FROM child WHERE id = ?");
        $stmt->bind_param("i", $childID);
        $stmt->execute();
        $stmt->bind_result($childString);
        $stmt->fetch();
        $stmt->close();

        // Add the child to the shopping basket
        $_SESSION['shopping_basket'][] = $childString;
    }
}

// Retrieve all children from the database
$children = [];
$stmt = $conn->prepare("SELECT id, string FROM child");
$stmt->execute();
$stmt->bind_result($childID, $childString);
while ($stmt->fetch()) {
    $children[] = [
        'id' => $childID,
        'string' => $childString
    ];
}
$stmt->close();

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
    <h3>All Children:</h3>
    <ul>
    <?php foreach ($children as $child) : ?>
        <li>
            <?php echo $child['string']; ?>
            <form action="" method="post" style="display:inline-block;">
                <input type="hidden" name="child_id" value="<?php echo $child['id']; ?>">
                <input type="submit" name="add_to_basket" value="Add to Basket">
            </form>
        </li>
    <?php endforeach; ?>
    </ul>
    <a href="viewShoppingBasket.php">View Shopping Basket</a>
    <a href="index.php">Back to Home</a>
</body>
</html>
