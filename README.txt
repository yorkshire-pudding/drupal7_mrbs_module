# WARNING
This is the old module that is insecure.  It is here for reference only


Drupal - MRBS integration



This very simple module offers single sign-on integration with MRBS ( http://mrbs.sourceforge.net/ ) and Drupal. The module uses Drupal user accounts, permissions and sessions with MRBS. Currently the module has only been tested when installed directly in a subdirectory on Drupal root directory, but it should be quite easy to modify it for other installations.

Installation
- Install MRBS in mrbs subdirectory on your Drupal installation
- Configure MRBS to use same database as Drupal and make sure it works with default auth and session handling
- Install Drupal module and enable it
- Set Drupal permissions for MRBS module at admin/user/permissions
- Copy auth_drupal.inc and session_drupal.inc from mrbs_inc subdirectory to your mrbs install directory
- Change config.inc.php:
  - $auth["session"] = "drupal";
  - $auth["type"] = "drupal";

That's it, MRBS users and sessions should now be managed by Drupal.
