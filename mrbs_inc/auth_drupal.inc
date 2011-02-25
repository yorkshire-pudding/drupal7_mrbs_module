<?php

 *
 * Authentication scheme that uses Drupal session to authenticate user
 *
 */

// Some local configuration
$mrbs_subdir = '/mrbs';

// Drupal bootstrap doesn't work if we don't play around with directories a bit
$base_dir = substr(getcwd(), 0, -1 * strlen($mrbs_subdir));
chdir($base_dir);
$base_root = (isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] == 'on') ? 'https' : 'http';

$base_url = $base_root .= '://'. preg_replace('/[^a-z0-9-:._]/i', '', $_SERVER['HTTP_HOST']);
if ($dir = trim(dirname($_SERVER['SCRIPT_NAME']), '\,/')) {
  $base_path = "/$dir";
  $base_url .= $base_path;
}
$base_url = substr($base_url, 0, -1 * strlen($mrbs_subdir));

// Drupal includes should now be in our current working directory
require_once './includes/bootstrap.inc';

// We need to do full bootstrap to get access to user permissions
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);


// Is it safe to remove the version check?
function version_check($vercheck)
{
  $minver = str_replace(".","", $vercheck);
  $curver = str_replace(".","", phpversion());

  if($curver >= $minver)
  {
    return true;
  }
  return false;
}

if (version_check("4.0.3") == false)
{
  include "escapeshellarg.inc";
}


/* authGetUserLevel($user)
 * 
 * Determines the users access level
 * 
 * $user - The user name
 *
 * Returns:
 *   The users access level
 */
function authGetUserLevel($not_required, $lev1_admin)
{
  if (user_access('administer mrbs')) {
	return 2;
  } elseif (user_access('make mrbs bookings')) {
	return 1;
  } else {
	return 0;
  }
}

?>
