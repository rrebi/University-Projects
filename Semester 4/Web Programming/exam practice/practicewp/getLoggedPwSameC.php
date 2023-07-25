<?php
require_once 'db.php';
session_start();

// Fetch the logged-in parent's ID and username
if (isset($_SESSION['parent_id']) && isset($_SESSION['username'])) {
    $loggedInParentID = $_SESSION['parent_id'];
    $loggedInParentName = $_SESSION['username'];

    // Fetch children of the logged-in parent
    $stmt = $conn->prepare("SELECT id, string, number, date FROM child WHERE idP = ?");
    $stmt->bind_param("s", $loggedInParentID);
    $stmt->execute();
    $result = $stmt->get_result();
    $children = $result->fetch_all(MYSQLI_ASSOC);

    // Fetch other parents who have the same child as the logged-in parent
    $otherParents = array(); // Array to store other parents
    foreach ($children as $child) {
        $stmt = $conn->prepare("SELECT DISTINCT p.username
                                FROM parent p
                                INNER JOIN child c ON p.id = c.idP
                                WHERE c.string = ? AND c.date = ? AND c.number=? AND c.idP <> ?");
        $stmt->bind_param("sssi", $child['string'], $child['date'], $child['number'], $loggedInParentID);
        $stmt->execute();
        $result = $stmt->get_result();
        $parents = $result->fetch_all(MYSQLI_ASSOC);

        // Add the parents to the array if they exist
        if (!empty($parents)) {
            $otherParents[$child['id']] = $parents;
        }
    }
}
?>

<!DOCTYPE html>
<html>
<head>
  <title>Parents with Same Child</title>
  <style>
    table {
      border-collapse: collapse;
      width: 100%;
    }
    th, td {
      border: 1px solid black;
      padding: 8px;
      text-align: center;
    }
  </style>
</head>
<body>
  <h1>All Children</h1>

  <?php if (empty($loggedInParentID)) { ?>
    <p>No parent found/not logged in.</p>
    <a href="login.php">Login</a>
  <?php } elseif (empty($children)) { ?>
    <p>No records found.</p>
  <?php } else { ?>
    <?php foreach ($children as $child) { ?>
      <?php if (isset($otherParents[$child['id']])) { ?>
        <h2>Child ID: <?php echo $child['id']; ?></h2>
        <table>
          <tr>
            <th>String</th>
            <th>Parent</th>
            <th>Actions</th>
          </tr>
          <tr>
            <td><?php echo $child['string']; ?></td>
            <td><?php echo $loggedInParentName; ?></td>
            <td>
              <a href="update.php?id=<?php echo $child['id']; ?>">Update</a> |
              <a href="delete.php?id=<?php echo $child['id']; ?>">Delete</a>
            </td>
          </tr>
        </table>
        <h3>Other Parents with the Same Child</h3>
        <ul>
          <?php foreach ($otherParents[$child['id']] as $parent) { ?>
            <li><?php echo $parent['username']; ?></li>
          <?php } ?>
        </ul>
      <?php } ?>
    <?php } ?>
  <?php } ?>
</body>
</html>
