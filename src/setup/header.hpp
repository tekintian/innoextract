
#ifndef INNOEXTRACT_SETUP_HEADER_HPP
#define INNOEXTRACT_SETUP_HEADER_HPP

#include <stdint.h>
#include <stddef.h>
#include <bitset>
#include <string>
#include <iosfwd>

#include "crypto/checksum.hpp"
#include "setup/windows.hpp"
#include "stream/chunk.hpp"
#include "util/enum.hpp"
#include "util/flags.hpp"

namespace setup {

struct version;

typedef char salt[8];

struct header {
	
	// Setup data header.
	
	FLAGS(flags,
		
		DisableStartupPrompt,
		CreateAppDir,
		AllowNoIcons,
		AlwaysRestart,
		AlwaysUsePersonalGroup,
		WindowVisible,
		WindowShowCaption,
		WindowResizable,
		WindowStartMaximized,
		EnableDirDoesntExistWarning,
		Password,
		AllowRootDirectory,
		DisableFinishedPage,
		ChangesAssociations,
		UsePreviousAppDir,
		BackColorHorizontal,
		UsePreviousGroup,
		UpdateUninstallLogAppName,
		UsePreviousSetupType,
		DisableReadyMemo,
		AlwaysShowComponentsList,
		FlatComponentsList,
		ShowComponentSizes,
		UsePreviousTasks,
		DisableReadyPage,
		AlwaysShowDirOnReadyPage,
		AlwaysShowGroupOnReadyPage,
		AllowUNCPath,
		UserInfoPage,
		UsePreviousUserInfo,
		UninstallRestartComputer,
		RestartIfNeededByRun,
		ShowTasksTreeLines,
		AllowCancelDuringInstall,
		WizardImageStretch,
		AppendDefaultDirName,
		AppendDefaultGroupName,
		EncryptionUsed,
		ChangesEnvironment,
		ShowUndisplayableLanguages,
		SetupLogging,
		SignedUninstaller,
		UsePreviousLanguage,
		DisableWelcomePage,
		
		// Obsolete flags
		Uninstallable,
		DisableDirPage,
		DisableProgramGroupPage,
		DisableAppendDir,
		AdminPrivilegesRequired,
		AlwaysCreateUninstallIcon,
		CreateUninstallRegKey,
		BzipUsed,
		ShowLanguageDialog,
		DetectLanguageUsingLocale,
		DisableDirExistsWarning,
		BackSolid,
		OverwriteUninstRegEntries
	);
	
	FLAGS(architecture_types,
		ArchitectureUnknown,
		X86,
		Amd64,
		IA64
	);
	
	std::string app_name;
	std::string app_versioned_name;
	std::string app_id;
	std::string app_copyright;
	std::string app_publisher;
	std::string app_publisher_url;
	std::string app_support_phone;
	std::string app_support_url;
	std::string app_updates_url;
	std::string app_version;
	std::string default_dir_name;
	std::string default_group_name;
	std::string uninstall_icon_name;
	std::string base_filename;
	std::string uninstall_files_dir;
	std::string uninstall_name;
	std::string uninstall_icon;
	std::string app_mutex;
	std::string default_user_name;
	std::string default_user_organisation;
	std::string default_serial;
	std::string app_readme_file;
	std::string app_contact;
	std::string app_comments;
	std::string app_modify_path;
	std::string create_uninstall_registry_key;
	std::string uninstallable;
	std::string license_text;
	std::string info_before;
	std::string info_after;
	std::string uninstaller_signature;
	std::string compiled_code;
	
	std::bitset<256> lead_bytes;
	
	size_t language_count;
	size_t message_count;
	size_t permission_count;
	size_t type_count;
	size_t component_count;
	size_t task_count;
	size_t directory_count;
	size_t file_count;
	size_t data_entry_count;
	size_t icon_count;
	size_t ini_entry_count;
	size_t registry_entry_count;
	size_t delete_entry_count;
	size_t uninstall_delete_entry_count;
	size_t run_entry_count;
	size_t uninstall_run_entry_count;
	
	windows_version_range winver;
	
	typedef uint32_t Color;
	Color back_color;
	Color back_color2;
	Color image_back_color;
	Color small_image_back_color;
	
	crypto::checksum password;
	salt password_salt;
	
	int64_t extra_disk_space_required;
	size_t slices_per_disk;
	
	enum install_verbosity {
		NormalInstallMode,
		SilentInstallMode,
		VerySilentInstallMode,
	};
	install_verbosity install_mode;
	
	enum log_mode {
		AppendLog,
		NewLog,
		OverwriteLog
	};
	log_mode uninstall_log_mode;
	
	enum style {
		ClassicStyle,
		ModernStyle
	};
	style uninstall_style;
	
	enum auto_bool {
		Auto,
		No,
		Yes
	};
	
	auto_bool dir_exists_warning;
	
	enum privilege_level {
		NoPrivileges,
		PowerUserPrivileges,
		AdminPriviliges,
		LowestPrivileges
	};
	privilege_level privileges_required;
	
	auto_bool show_language_dialog;
	
	enum language_detection_method {
		UILanguage,
		LocaleLanguage,
		NoLanguageDetection
	};
	language_detection_method language_detection;
	
	stream::compression_method compression;
	
	architecture_types architectures_allowed;
	architecture_types architectures_installed_in_64bit_mode;
	
	uint32_t signed_uninstaller_original_size;
	uint32_t signed_uninstaller_header_checksum;
	
	auto_bool disable_dir_page;
	auto_bool disable_program_group_page;
	
	size_t uninstall_display_size;
	
	flags options;
	
	void load(std::istream & is, const version & version);
	
};

} // namespace setup

NAMED_FLAGS(setup::header::flags)
NAMED_FLAGS(setup::header::architecture_types)
NAMED_ENUM(setup::header::install_verbosity)
NAMED_ENUM(setup::header::log_mode)
NAMED_ENUM(setup::header::style)
NAMED_ENUM(setup::header::auto_bool)
NAMED_ENUM(setup::header::privilege_level)
NAMED_ENUM(setup::header::language_detection_method)

#endif // INNOEXTRACT_SETUP_HEADER_HPP