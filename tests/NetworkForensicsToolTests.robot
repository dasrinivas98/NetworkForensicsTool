*** Settings ***
Library           Process
Library           String
Library           Collections

*** Variables ***
${EXECUTABLE}    ../build/Debug/NetworkForensicsTool.exe  # Adjust this path as needed
${MALICIOUS_KEYWORDS}    malicious, attack, exploit, hack, unauthorized

*** Test Cases ***

# Test to check if the application runs successfully
Application Should Run Successfully
    [Documentation]    Test if the server application runs without errors.
    ${result}=    Run Process    ${EXECUTABLE}    
    Should Be Equal As Strings    ${result.rc}    0    # Check if exit code is 0 (successful)
    Should Not Contain    ${result.stdout}    Error

# Test to validate detection of malicious packets
Should Detect Malicious Packets
    [Documentation]    Check that malicious packets are correctly detected in the output.
    ${result}=    Run Process    ${EXECUTABLE}
    ${output}=    Set Variable    ${result.stdout}
    ${malicious_packets}=    Evaluate    [line for line in '''${output}'''.splitlines() if 'Malicious Packet Detected' in line]
    Should Be True    ${malicious_packets}
    Log Many    ${malicious_packets}

# Test to verify packet information formatting
Should Display Packet Info Correctly
    [Documentation]    Validate that packet details (size and timestamp) are present for each packet.
    ${result}=    Run Process    ${EXECUTABLE}
    ${output}=    Set Variable    ${result.stdout}
    ${lines}=      Split String    ${output}    \n
    FOR    ${line}    IN    @{lines}
        Should Match Regexp    ${line}    .*Packet.*Size: [0-9]+ bytes.*Timestamp:.*  # Check size and timestamp presence
    END
