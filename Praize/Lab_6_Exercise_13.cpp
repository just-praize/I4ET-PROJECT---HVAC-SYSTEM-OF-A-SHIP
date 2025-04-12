pragma solidity ^ 0.8.18;

import "@openzeppelin/contracts/access/Ownable.sol";

// This contract inherits OpenZeppelin's Ownable, giving it access to modifier `onlyOwner`
contract OwnableExample is Ownable
{

    string private secret;
    string public publicMessage;

    constructor()
    {
        publicMessage = "Welcome to the smart contract!";
        secret = "Only the owner knows this.";
    }

    // This function can only be called by the owner (msg.sender == owner)
    function updateSecret(string memory _newSecret) public onlyOwner
    {
        secret = _newSecret;
    }

    // Anyone can read this
    function getPublicMessage() public view returns(string memory)
    {
        return publicMessage;
    }

    // Only the owner can view the secret
    function getSecret() public view onlyOwner returns(string memory)
    {
        return secret;
    }

    // Owner can update the public message
    function updatePublicMessage(string memory _newMessage) public onlyOwner
    {
        publicMessage = _newMessage;
    }
}
