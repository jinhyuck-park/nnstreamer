#!/usr/bin/env bash

##
# @file config-plugins-audit.sh
# @brief add plugin modules for a github repository
# @see      https://github.sec.samsung.net/STAR/TAOS-CI
# @author   Geunsik Lim <geunsik.lim@samsung.com>


###### plugins-base ###############################################################################################
echo "[MODULE] plugins-base: Basis plugins with good quality"
# Please append your plugin modules here.

module_name="pr-audit-build-tizen"
echo "[DEBUG] $module_name is started."
echo "[DEBUG] TAOS/$module_name: Check if Tizen rpm package is successfully generated."
echo "[DEBUG] Current path: $(pwd)."
source ${REFERENCE_REPOSITORY}/ci/standalone/plugins-base/$module_name.sh
# Note that do not append the below "$module_name" because build step is implemented as a built-in module partially
# $module_name
echo "[DEBUG] $module_name is done."

module_name="pr-audit-build-ubuntu"
echo "[DEBUG] $module_name is started."
echo "[DEBUG] TAOS/$module_name: Check if Ubuntu deb package is successfully generated."
echo "[DEBUG] Current path: $(pwd)."
source ${REFERENCE_REPOSITORY}/ci/standalone/plugins-base/$module_name.sh
# Note that do not append the below "$module_name" because build step is implemented as a built-in module partially
# $module_name
echo "[DEBUG] $module_name is done."

###### plugins-good ###############################################################################################
echo "[MODULE] plugins-good: Plugins with good quality"
# Please append your plugin modules here.






###### plugins-staging ################################################################################################
echo "[MODULE] plugins-staging: Plugins without enough evaluation and aging test"
# Please append your plugin modules here.

module_name="pr-audit-resource"
echo "[DEBUG] $module_name is started."
echo "[DEBUG] TAOS/$module_name: Check if there are not-installed resource files."
echo "[DEBUG] Current path: $(pwd)."
source ${REFERENCE_REPOSITORY}/ci/standalone/plugins-staging/$module_name.sh
$module_name
echo "[DEBUG] $module_name is done."

